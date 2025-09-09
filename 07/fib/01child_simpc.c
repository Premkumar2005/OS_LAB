// fib.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    if (n < 1)
        return 1;

    int shm_fd = shm_open("VSS", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    char *ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    int a = 0, b = 1;
    sprintf(ptr, "%d ", a);
    ptr += strlen(ptr);
    if (n > 1)
    {
        sprintf(ptr, "%d ", b);
        ptr += strlen(ptr);
    }

    for (int i = 2; i < n; ++i)
    {
        int c = a + b;
        sprintf(ptr, "%d ", c);
        ptr += strlen(ptr);
        a = b;
        b = c;
    }

    return 0;
}
// gcc parent.c -o parent -lrt
// gcc fib.c -o fib -lrt
// ./parent 6
