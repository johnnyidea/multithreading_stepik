#include <iostream>

#include <sys/socket.h>
#include <csignal>

int main(int argc, char** argv)
{
    int sv[2];
    int fd_ps = socketpair(AF_UNIX, SOCK_STREAM, 0, sv);

    if (fd_ps < 0)
    {
        perror("Socket pair");
        exit(EXIT_FAILURE);
    }

    int pid_child = fork();
    int b_sz{512};
    char buffer[b_sz];
    //parent
    if (pid_child == 0)
        while (true)
        {
            char msg[] = "Hello from parent";
            write(sv[0], msg, sizeof(msg));
        }
    //child
    else if (pid_child > 0)
        while (true)
        {
            read(sv[1], buffer, b_sz);
            std::cout << buffer << std::endl;
        }
    else
    {
        perror("Problem with pid");
        exit(EXIT_FAILURE);
    }
    return 0;
}