
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char** argv)
{
	int sckt_fd = socket(AF_INET, // domain - IPv4
                         SOCK_STREAM, // type - TCP
                         IPPROTO_TCP); // protocol

	struct sockaddr_in address;
	
	if (sckt_fd  < 0 )
	{
		perror ("Couldn't create server socket");
		return -1;
	}

	address.sin_family = AF_INET;
	address.sin_port = htons(12345);
	address.sin_addr.s_addr = htonl(INADDR_ANY); //0.0.0.0

	if (bind(sckt_fd, (struct sockaddr*)&(address), sizeof(address)) < 0)
	{
		perror("Couldn't bind server socket");
		return -1;
	}

	listen(sckt_fd, SOMAXCONN);

	while(1)
	{
		int slave_socket = accept(sckt_fd, 0, 0);
		int buffer[5] = {0, 0, 0, 0, 0};
		recv(slave_socket, buffer, 4, MSG_NOSIGNAL);
        send(slave_socket, buffer, 4, MSG_NOSIGNAL);
		shutdown(slave_socket, SHUT_RDWR);
		close(slave_socket);
		printf("%s \n", buffer);
	}

	return 0;
}


