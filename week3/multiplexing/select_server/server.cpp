#include <iostream>
#include <set>
#include <algorithm>

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

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

    set_nonblock(master_socket_fd);

    if (bind(master_socket_fd, (struct sockaddr*)&s_addr, sizeof(s_addr)) < 0)
    {
        perror("Couldn't bind socket");
        exit(EXIT_FAILURE);
    }

    if (listen(master_socket_fd, SOMAXCONN) < 0)
    {
        perror("Couldn't listen");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        fd_set set_of_fd;
        FD_ZERO(&set_of_fd);
        FD_SET(master_socket_fd, &set_of_fd);

        for (auto it = slave_sockets.begin(); it != slave_sockets.end(); it++)
            FD_SET(*it, &set_of_fd);

        int max_fd = max(master_socket_fd, *max_element(slave_sockets.begin(), slave_sockets.end()));

        select(max_fd + 1, &set_of_fd, nullptr, nullptr, nullptr);
        // we get ones in positions that are worked
        for (auto it = slave_sockets.begin(); it != slave_sockets.end(); it++)
            if (FD_ISSET(*it, &set_of_fd))
            {
                static char buffer [1024];
                int rec_sz = recv(*it, buffer, 1024, MSG_NOSIGNAL);

                if ((rec_sz == 0) && (errno != EAGAIN))
                {
                    shutdown(*it, SHUT_RDWR);
                    close(*it);
                    slave_sockets.erase(it);
                } else
                    send(*it, buffer, 1024, MSG_NOSIGNAL);
            }

        if (FD_ISSET(master_socket_fd, &set_of_fd))
        {
            int new_slave_socket = accept(master_socket_fd, 0, 0);
            set_nonblock(master_socket_fd);
            slave_sockets.insert(new_slave_socket);
        }

        cout << "main socket id:" << master_socket_fd << endl;
        for (const auto it: slave_sockets)
            cout << it << endl;
    }

    return 0;
}