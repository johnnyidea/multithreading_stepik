// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd1;

    char* fifo_out_path = "/home/rene/education/multithreading_stepik/week5/fifo_pipe/out.fifo";

    mkfifo(fifo_out_path, 0666);

    char str1[512], str2[512];
    while (1)
    {
        // First open in read only and read
        fd1 = open(fifo_out_path, O_RDONLY);
        read(fd1, str1, 512);

        // Print the read string and close
        printf("User1: %s\n", str1);
        close(fd1);

        // Now open in write mode and write
        // string taken from user.
        fd1 = open(fifo_out_path, O_WRONLY);
        fgets(str2, 512, stdin);
        write(fd1, str2, strlen(str2)+1);
        close(fd1);
    }
    return 0;
}