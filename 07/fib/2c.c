#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

int main(int argc, char *argv[])
{
    int k = 2, n1 = 0, n2 = 1, n3;
    void *ptr;
    int i;

    if (argc != 2)
    {
        printf("Error: Missing N\n");
        return 1;
    }

    i = atoi(argv[1]);

    // Access shared memory with key 1122
    int shmid = shmget((key_t)1122, 4096, 0666);
    ptr = shmat(shmid, NULL, 0);

    printf("CHILD:\n");
    sprintf(ptr, "%d ", n1);
    ptr += strlen((char *)ptr);
    sprintf(ptr, "%d ", n2);
    ptr += strlen((char *)ptr);

    printf("%d ", n1);
    printf("%d ", n2);

    while (k < i)
    {
        n3 = n1 + n2;
        sprintf(ptr, "%d ", n3);
        printf("%d ", n3);
        n1 = n2;
        n2 = n3;
        ptr += strlen((char *)ptr);
        k++;
    }

    printf("\n");
    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
/*
cc parent.c -o parent
cc fib.c -o fib
./parent 6
*/