#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

int main()
{
    void *psm;
    char buf[10];
    int shmid;

    // 1. Create shared memory object
    shmid = shm_open("shared_mem", O_CREAT | O_RDWR, 0666);

    // 2. Set size of shared memory
    ftruncate(shmid, 1024);

    // 3. Map memory to process address space
    psm = mmap(0, 1024, PROT_WRITE, MAP_SHARED, shmid, 0);

    printf("Key/ID of shared memory: %d\n", shmid);
    printf("Shared memory is attached at: %p\n", psm);

    printf("Enter data to write to shared memory:\n");
    read(0, buf, 10);

    // 4. Write data to shared memory
    sprintf(psm, "%s", buf);

    return 0;
}
