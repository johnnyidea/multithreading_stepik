#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <csignal>

int main(int argc, char** argv)
{
    int fd_in{0};
    char* fifo_in_path = "/home/box/in.fifo";
    mkfifo(fifo_in_path, 0666);

    int fd_out{0};
    char* fifo_out_path = "/home/box/out.fifo";
    mkfifo(fifo_out_path, 0666);

    int msg_sz{512};
    char msg[msg_sz];
    while (true)
    {
        fd_in = open(fifo_in_path, O_RDONLY);
        read(fd_in, msg, sizeof(msg));
        close(fd_in);

        fd_out = open(fifo_out_path, O_WRONLY);
        write(fd_out, msg, strlen(msg) + 1);
        close(fd_out);
    }

	return 0;
}