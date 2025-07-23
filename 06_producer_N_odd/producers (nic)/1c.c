#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    void *psm;
    int shmid;

    // 1. Open existing shared memory
    shmid = shm_open("shared_mem", O_RDONLY, 0666);

    // 2. Resize (optional) and map for reading
    ftruncate(shmid, 1024);
    psm = mmap(0, 1024, PROT_READ, MAP_SHARED, shmid, 0);

    printf("Key/ID of shared memory: %d\n", shmid);
    printf("Shared memory for consumer is attached at: %p\n", psm);
    printf("Data read from shared memory: %s\n", (char *)psm);

    // 3. Remove the shared memory object
    shm_unlink("shared_mem");

    return 0;
}
