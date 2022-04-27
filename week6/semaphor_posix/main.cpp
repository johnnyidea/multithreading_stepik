#include <iostream>

#include <semaphore.h>
#include <fcntl.h>

int main()
{
    auto sem = sem_open("/test.sem", O_CREAT, 0644, 66);

    while (1)
    {}
    return 0;
}
