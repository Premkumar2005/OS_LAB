#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    void *shared_memory;
    char buffer[100];
    int shmid;

    // Create shared memory segment
    shmid = shmget((key_t)1122, 1024, 0666 | IPC_CREAT);
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

    printf("Enter data to write to shared memory: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Write to shared memory
    strcpy(shared_memory, buffer);
    printf("Written: %s\n", (char *)shared_memory);

    return 0;
}
