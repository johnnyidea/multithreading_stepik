#include <iostream>
#include <set>
#include <algorithm>

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>

#define POLL_SIZE 2048 //events number that we can return or number of descriptors we can handle

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

    struct pollfd set_of_fd[POLL_SIZE];
    set_of_fd[0].fd = master_socket_fd;
    set_of_fd[0].events = POLLIN;

    while (true)
    {
        uint index{1};
        for (auto it = slave_sockets.begin(); it != slave_sockets.end(); it++)
        {
            set_of_fd[index].fd = *it;
            set_of_fd[index].events = POLLIN;
            index++;
        }

        size_t polls_sz = slave_sockets.size() + 1;

        poll(set_of_fd, polls_sz, -1);

        for (int i = 0; i < polls_sz; i++)
            if (set_of_fd[i].revents && POLLIN)
                if (i)
                {
                    static char buffer[1024];
                    int recv_sz = recv(set_of_fd[i].fd, buffer, 1024, MSG_NOSIGNAL);
                    if (recv_sz == 0 && errno != EAGAIN)
                    {
                        shutdown(set_of_fd[i].fd, SHUT_RDWR);
                        close(set_of_fd[i].fd);
                        slave_sockets.erase(set_of_fd[i].fd);
                    } else if (recv_sz > 0)
                        send(set_of_fd[i].fd, buffer, 1024, MSG_NOSIGNAL);
                } else
                {
                    int new_slave_socket = accept(master_socket_fd, 0, 0);
                    set_nonblock(new_slave_socket);
                    slave_sockets.insert(new_slave_socket);
                }

        cout << "main socket id:" << master_socket_fd << endl;
        for (const auto it: slave_sockets)
            cout << it << endl;
    }

    return 0;
}