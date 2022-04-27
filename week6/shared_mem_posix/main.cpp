#include <iostream>
#include <stdexcept>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>


int main()
{
    int megabyte = 1024*1024;
    auto fd = shm_open("/test.shm", O_CREAT| O_WRONLY,  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

    if (ftruncate(fd, megabyte) < 0)
        throw std::runtime_error{"Cannot truncate"};

    char *memory = static_cast<char*>(mmap(nullptr, megabyte, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    memset(memory, static_cast<char>(13), megabyte);

    while (1){}

    return 0;
}
