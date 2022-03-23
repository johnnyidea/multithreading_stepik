
#include <iostream>
#include <sys/socket.h> //socket
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_pton
#include <csignal>
#include <cstring>

#define PORT 8080

using namespace std;

int main(int argc, char** argv)
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;

//
//    int socket_fd {0};
//    struct sockaddr_in server_address_ipv4;
//    char buffer[1024];
//
//    if (socket_fd = socket(AF_INET, SOCK_STREAM, 0) < 0)
//    {
//        std::cerr << "Socket creation failed for client ";
//        return -1;
//    }
//
//    server_address_ipv4.sin_family = AF_INET;
//    server_address_ipv4.sin_port = htons(PORT);
//
//    if (inet_pton(AF_INET, "127.0.0.1", &server_address_ipv4.sin_addr) <= 0)
//    {
//        printf("\nInvalid address/ Address not supported \n");
//        return -1;
//    }
//
//    if ( connect(socket_fd, (struct sockaddr*)&server_address_ipv4, sizeof(server_address_ipv4)) < 0 )
//    {
//        printf("\nConnection Failed \n");
//        return -1;
//    }
//
//    recv(socket_fd, buffer, 1024, MSG_NOSIGNAL);
//
//    cout << buffer << endl;

	return 0;
}
