// fib.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int k = 2, n1 = 0, n2 = 1, n3;
    void *ptr;
    int n = atoi(argv[1]);
    int shm_fd = shm_open("VSS", O_CREAT | O_RDWR, 0666);

    ftruncate(shm_fd, 4096);
    ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("CHILD\n");

    // Writing Fibonacci sequence into shared memory as formatted string
    sprintf(ptr, "%d ", n1);
    ptr += strlen(ptr);
    sprintf(ptr, "%d ", n2);
    ptr += strlen(ptr);

    while (k < n)
    {
        n3 = n1 + n2;
        sprintf(ptr, "%d ", n3);
        ptr += strlen(ptr);
        n1 = n2;
        n2 = n3;
        k++;
    }

    return 0;
}
/*
!gcc p.c -o parent -lrt
!gcc c.c -o fib -lrt
!./parent 6
*/