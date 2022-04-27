#include <iostream>
#include <set>
#include <algorithm>

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>

#define MAX_EVENTS 32

using namespace std;

int set_nonblock(int fd)
{
    int flags;

#if defined(O_NONBLOCK)
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;

    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    flags = 1;
    return fcntl(fd, FIOBIO, &flags);
#endif
}

int main(int argc, char** argv)
{
    int opt{1};

    int master_socket_fd = socket(AF_INET,
                                  SOCK_STREAM,
                                  IPPROTO_TCP);

    set<int> slave_sockets;

    if (master_socket_fd < 0)
    {
        perror("Socket didn't create");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(master_socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in s_addr;

    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(12345);
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(master_socket_fd, (struct sockaddr*)&s_addr, sizeof(s_addr)) < 0)
    {
        perror("Couldn't bind socket");
        exit(EXIT_FAILURE);
    }

    set_nonblock(master_socket_fd);

    if (listen(master_socket_fd, SOMAXCONN) < 0)
    {
        perror("Couldn't listen");
        exit(EXIT_FAILURE);
    }

    int e_poll = epoll_create1(0);
    struct epoll_event event;
    event.data.fd = master_socket_fd;
    event.events = EPOLLIN;// access to read
    epoll_ctl(e_poll, EPOLL_CTL_ADD, master_socket_fd, &event);

    while (true)
    {
        struct epoll_event events[MAX_EVENTS];
        int n = epoll_wait(e_poll, events, MAX_EVENTS, -1); //-1 inf wait

        for (uint i = 0; i < n; i++)
            if (events[i].data.fd == master_socket_fd)
            {
                int new_slave_socket = accept(master_socket_fd, 0, 0);
                set_nonblock(new_slave_socket);
                struct epoll_event event;
                event.data.fd = new_slave_socket;
                event.events = EPOLLIN;
                epoll_ctl(e_poll, EPOLL_CTL_ADD, new_slave_socket, &event);
            } else
            {
                static char buf[1024];
                int recv_sz = recv(events[i].data.fd, buf, 1024, MSG_NOSIGNAL);
                if (recv_sz == 0 && errno != EAGAIN)
                {
                    shutdown(events[i].data.fd, SHUT_RDWR);
                    close(events[i].data.fd);
                } else if (recv_sz > 0)
                    send(events[i].data.fd, buf, recv_sz, MSG_NOSIGNAL);
            }

    }

    return 0;
}