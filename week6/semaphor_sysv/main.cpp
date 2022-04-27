#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

int main()
{
    int semaphores_num = 16;

    key_t key = ftok("/tmp/sem.temp", 1);

    //create semaphores group
    auto id = semget(key, semaphores_num, IPC_CREAT| 0777);

    std::cout << "sem id = " << id << std::endl;
    if (id  < 0)
    {
        perror("Sem creation failed");
        exit(EXIT_FAILURE);
    }

    union semun u;

    //set up semaphores
    for (int i = 0; i < semaphores_num; i++)
    {
        u.val = i;
        if (semctl(id, i, SETVAL, u) < 0)
        {
            perror("semctl");
            exit(EXIT_FAILURE);
        }
    }
    while(1)
    {}

    return 0;
}
