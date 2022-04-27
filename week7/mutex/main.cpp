#include <iostream>
#include <fstream>
#include <csignal>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_spinlock_t spin_lock;
pthread_rwlock_t rw_lock_w = PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_t rw_lock_r = PTHREAD_RWLOCK_INITIALIZER;

void* func_for_mutex(void* args)
{
    if (pthread_mutex_lock(static_cast<pthread_mutex_t*>(args)) != 0)
    {
        perror("mutex lock");
        exit(EXIT_FAILURE);
    }
    std::cout << "in thread mutex" << std::endl;
    if (pthread_mutex_unlock(static_cast<pthread_mutex_t*>(args)) != 0)
    {
        perror("mutex unlock");
        exit(EXIT_FAILURE);
    }

    return NULL;
}

void* func_for_spinlock(void* args)
{
    if (pthread_spin_lock(static_cast<pthread_spinlock_t*>(args)) != 0)
    {
        perror("spin lock");
        exit(EXIT_FAILURE);
    }

    std::cout << "in thread spinlock" << std::endl;

    if (pthread_spin_unlock(static_cast<pthread_spinlock_t*>(args)) != 0)
    {
        perror("spin unlock");
        exit(EXIT_FAILURE);
    }

    return NULL;
}

void* func_for_rw_w(void* args)
{
    if (pthread_rwlock_wrlock(static_cast<pthread_rwlock_t *>(args)) != 0)
    {
        perror("rw w lock");
        exit(EXIT_FAILURE);
    }

    std::cout << "in thread rw write" << std::endl;

    if (pthread_rwlock_unlock(static_cast<pthread_rwlock_t *>(args)) != 0)
    {
        perror("rw w unlock");
        exit(EXIT_FAILURE);
    }

    return NULL;
}

void* func_for_rw_r(void* args)
{
    if (pthread_rwlock_rdlock(static_cast<pthread_rwlock_t *>(args)) != 0)
    {
        perror("rw w lock");
        exit(EXIT_FAILURE);
    }

    std::cout << "in thread rw read" << std::endl;

    if (pthread_rwlock_unlock(static_cast<pthread_rwlock_t *>(args)) != 0)
    {
        perror("rw w unlock");
        exit(EXIT_FAILURE);
    }

    return NULL;
}


int main()
{
    int pid_process = getpid();
    std::ofstream f("/home/box/main.pid");
    f << pid_process;
    f.close();

    pthread_t threads[4];

    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------

    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        perror("mutex init");
        exit(EXIT_FAILURE);
    }

    if (pthread_mutex_lock(&mutex) != 0)
    {
        perror("mutex lock");
        exit(EXIT_FAILURE);
    }

    //wait for mutex unlock
    if (pthread_create(&threads[0], NULL, func_for_mutex, (void *)&mutex) < 0)
    {
        perror("thread mutex is not created");
        exit(EXIT_FAILURE);
    }

    if (pthread_mutex_unlock(&mutex) != 0)
    {
        perror("mutex unlock");
        exit(EXIT_FAILURE);
    }

    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------

    if (pthread_spin_init(&spin_lock, PTHREAD_PROCESS_PRIVATE) != 0)
    {
        perror("spinlock init");
        exit(EXIT_FAILURE);
    }

    if (pthread_spin_lock(&spin_lock) != 0)
    {
        perror("spin lock");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&threads[1], NULL, func_for_spinlock, (void *)&spin_lock) < 0)
    {
        perror("thread spinlock is not created");
        exit(EXIT_FAILURE);
    }

    if (pthread_spin_unlock(&spin_lock) != 0)
    {
        perror("spin unlock");
        exit(EXIT_FAILURE);
    }

    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------

    if (pthread_rwlock_init(&rw_lock_w, NULL) != 0)
    {
        perror("rwlock w init");
        exit(EXIT_FAILURE);
    }

    if (pthread_rwlock_wrlock(&rw_lock_w) != 0)
    {
        perror("rw w lock");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&threads[2], NULL, func_for_rw_w, (void *) &rw_lock_w) < 0)
    {
        perror("thread rwlock w is not created");
        exit(EXIT_FAILURE);
    }

    if (pthread_rwlock_unlock(&rw_lock_w) != 0)
    {
        perror("rw w unlock");
        exit(EXIT_FAILURE);
    }

    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------

    if (pthread_rwlock_init(&rw_lock_r, NULL) != 0)
    {
        perror("rwlock r init");
        exit(EXIT_FAILURE);
    }

    if (pthread_rwlock_rdlock(&rw_lock_r) != 0)
    {
        perror("rw r lock");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&threads[3], NULL, func_for_rw_r, (void *) &rw_lock_r) < 0)
    {
        perror("thread rwlock r is not created");
        exit(EXIT_FAILURE);
    }

    if (pthread_rwlock_unlock(&rw_lock_r) != 0)
    {
        perror("rw w unlock");
        exit(EXIT_FAILURE);
    }

    //-------------------------------------------------------------------------

    sleep(1);

    //-------------------------------------------------------------------------

    if (pthread_mutex_destroy(&mutex) != 0)
    {
        perror("mutex destroy");
        exit(EXIT_FAILURE);
    }
    //-------------------------------------------------------------------------
    if (pthread_spin_destroy(&spin_lock) != 0)
    {
        perror("spinlock destroy");
        exit(EXIT_FAILURE);
    }
    //-------------------------------------------------------------------------
    if (pthread_rwlock_destroy(&rw_lock_w) != 0)
    {
        perror("rw lock w destroy");
        exit(EXIT_FAILURE);
    }
    //-------------------------------------------------------------------------
    if (pthread_rwlock_destroy(&rw_lock_r) != 0)
    {
        perror("rw lock r destroy");
        exit(EXIT_FAILURE);
    }
    //-------------------------------------------------------------------------
    for (int i = 0; i < 4; i++)
        pthread_join(threads[i],NULL);


    return 0;
}
