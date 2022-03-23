#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char** argv)
{
    int socket_fd = socket(AF_INET,
                           SOCK_STREAM,
                           IPPROTO_TCP); //domain, type, protocol

    if (socket_fd < 0)
    {
        perror("Socket creation failed");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("Connection error");
        return -1;
    }

    char buffer [] = "Mooo";

    send(socket_fd, buffer, 4, MSG_NOSIGNAL);
    recv(socket_fd, buffer, 4, MSG_NOSIGNAL);

    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    printf("%s\n", buffer);

    return 0;
}

