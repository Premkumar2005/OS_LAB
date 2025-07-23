#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    void *shared_memory;
    int shmid;

    // Access shared memory segment
    shmid = shmget((key_t)1122, 1024, 0666);
    if (shmid < 0)
    {
        perror("shmget failed");
        exit(1);
    }

    // Attach segment to data space
    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    printf("Data read from shared memory: %s\n", (char *)shared_memory);

    // Detach the shared memory
    shmdt(shared_memory);

    return 0;
}
