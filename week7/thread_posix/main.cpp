#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fstream>
#include <csignal>

void* func(void* arg)
{
    std::cout<< *(std::string *)arg << std::endl;
    pause();
    return NULL;
}

int main()
{
    auto pid_process = getpid();

    std::ofstream f("/home/box/main.pid");
    f << pid_process;
    f.close();

    pthread_t thrd1;
    std::string msg("Thread will wait until signal");

    if (pthread_create(&thrd1, NULL, func, (void*)&msg) < 0)
    {
        perror("thread is not created");
        exit(EXIT_FAILURE);
    }

    pthread_join(thrd1, NULL);

    return 0;
}
