
#include <iostream>
#include <sys/socket.h> // socket
#include <netinet/in.h>
#include <arpa/inet.h> // inet_addr
#include <sys/un.h> // struct sockaddr_un
#include <csignal> // SIGPIPE

#define PORT 8080


int main(int argc, char ** argv)
{

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");

//    int server_fd, new_socket, valread;
//    int opt = 1;
//    //ipv4
//    struct sockaddr_in address_v4;
////    struct sockaddr_in6 address_v6;
//
//    auto s_fd = socket(AF_INET, SOCK_STREAM, 0);
//
//    if (s_fd == 0)
//    {
//        perror("Socket creation failed for server");
//        exit(EXIT_FAILURE);
//    }
//
//    // Forcefully attaching socket to the port 8080
//    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
//                   &opt, sizeof(opt)))
//    {
//        perror("setsockopt");
//        exit(EXIT_FAILURE);
//    }
//
//    // set port to socket ??
//    address_v4.sin_family = AF_INET; //IPv4
//    address_v4.sin_port = htons(PORT);
//    address_v4.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1 when server runs on a local machine
//
//
////    address_v4.sin_addr.s_addr = INADDR_LOOPBACK; // 0.0.0.0 socket for all addresses
//
//    // convert string ip address_v4
////    auto ip = inet_addr("10.0.0.1"); //only for ipv4
//    //more convenient
////    auto ip = inet_pton(AF_INET, "10.0.0.1", &address_v4);
//
//
////    struct sockaddr_un address_un;
////    address_un.sun_family = AF_UNIX;
////    strcpy(address_un.sun_path, "/tmp/a.sock");
//
//    if (bind(s_fd, (struct sockaddr*)& address_v4, sizeof(address_v4)) < 0)
//    {
//        perror("Bind error");
//        exit(EXIT_FAILURE);
//    }
//
//    listen(s_fd, SOMAXCONN);
//
//    int s1{0};
//
//    char buffer[1024];
//    char* msg = "Hello from server.";
//
////    accept(s_fd, struct sockaddr * , 0) - last two args - it is a pair of ip address and port AND size of struct
//    while (s1 = accept(s_fd, 0, 0))
//    {
//        auto r_sz = recv(s1, buffer, 1024, MSG_NOSIGNAL);
//        auto w_sz = send(s1, msg, strlen(msg), MSG_NOSIGNAL);
//    }
//
//
////    SIGPIPE;
////    signal(SIGPIPE, SIG_IGN);
////    auto r_sz = read(s1, buffer, 1024);
////    auto w_sz = write(s1, msg, strlen(msg));
////    SIGPIPE;
////    signal(SIGPIPE, SIG_IGN);

	return 0;
}

