#include <iostream>
#include <sys/stat.h>
//#include <bits/fcntl.h>
#include <fcntl.h>
#include <cstring>
#include <csignal>

int main(int argc, char** argv)
{
    int fd{0};
    char* fifo_in_path = "/home/rene/education/multithreading_stepik/week5/fifo_pipe/in.fifo";
    mkfifo(fifo_in_path, 0666);

    char arr1[80], arr2[80];
    while (1)
    {
        // Open FIFO for write only
        fd = open(fifo_in_path, O_WRONLY);

        // Take an input arr2ing from user.
        // 80 is maximum length
        fgets(arr2, 80, stdin);

        // Write the input arr2ing on FIFO
        // and close it
        write(fd, arr2, strlen(arr2)+1);
        close(fd);

        // Open FIFO for Read only
        fd = open(fifo_in_path, O_RDONLY);

        // Read from FIFO
        read(fd, arr1, sizeof(arr1));

        // Print the read message
        printf("User2: %s\n", arr1);
        close(fd);
    }

	return 0;
}