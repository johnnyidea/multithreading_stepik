#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <algorithm>

int main()
{
    key_t key = ftok("/tmp/mem.temp", 1);

    int sh_mem_sz = 1024 * 1024;

    auto segment_id = shmget (key, sh_mem_sz,
                              IPC_CREAT|0666);

    printf("Segment ID %d\n", segment_id);

    char *sh_mem = (char *) shmat(segment_id, (void*)0, 0);

    std::fill(sh_mem, sh_mem + sh_mem_sz, static_cast<char>(42));

    return 0;
}
