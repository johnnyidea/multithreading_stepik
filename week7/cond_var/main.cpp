#include <iostream>
#include <pthread.h>
#include <fstream>
#include <csignal>
#include <unistd.h>

struct MutexCond
{
    pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_barrier_t barrier;
    int counter = 1;
} mutex_cond;

void* func_cond(void* args)
{
    auto mtx_cnd = (struct MutexCond *)args;

//    if (pthread_barrier_wait(&mtx_cnd->barrier) != 0)
//    {
//        perror("barrier wait th 0");
//        exit(EXIT_FAILURE);
//    }
//
//    std::cout << "Barrier thread 0 reached" << std::endl;

    if (pthread_mutex_lock(&mtx_cnd->mtx) != 0)
    {
        perror("mutex lock");
        exit(EXIT_FAILURE);
    }

    if (pthread_cond_wait(&mtx_cnd->cond, &mtx_cnd->mtx) != 0)
    {
        perror("cond wait");
        exit(EXIT_FAILURE);
    }
    std::cout << "Success wait cond" << std::endl;

    if (pthread_mutex_unlock(&mtx_cnd->mtx) != 0)
    {
        perror("mutex unlock");
        exit(EXIT_FAILURE);
    }

    std::cout << "Success wait cond" << std::endl;


    printf("Returning thread\n");

    return NULL;
}

void* func_barrier(void* args)
{
    auto mtx_cnd = (struct MutexCond *)args;

    int bar_val;
    if (bar_val = pthread_barrier_wait(&mtx_cnd->barrier) != 0)
    {
//        perror("barrier wait th1");
//        exit(EXIT_FAILURE);
    }

    std::cout << "Barrier thread 1 reached" << std::endl;

    return NULL;
}

int main()
{
    int pid_p = getpid();
    std::ofstream f("/home/box/main.pid");
    f << pid_p;
    f.close();

    pthread_t threads[2];

    if (pthread_cond_init(&mutex_cond.cond, NULL) != 0)
    {
        perror("cond init");
        exit(EXIT_FAILURE);
    }

    pthread_barrier_init(&mutex_cond.barrier, NULL, 1);

    if (pthread_create(&threads[0], NULL, func_cond, (void*)&mutex_cond) < 0)
    {
        perror("thread cond is not created");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&threads[1], NULL, func_barrier, (void*)&mutex_cond) < 0)
    {
        perror("thread barrier is not created");
        exit(EXIT_FAILURE);
    }

    sleep(1);



    if (pthread_barrier_destroy(&mutex_cond.barrier) != 0)
    {
        perror("barrier destroy");
        exit(EXIT_FAILURE);
    }

    if (pthread_cond_signal(&mutex_cond.cond) != 0)
    {
        perror("failed to send cond sig");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2; i++)
        pthread_join(threads[i],NULL);

    return 0;
}
