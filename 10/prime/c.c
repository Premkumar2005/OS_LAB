#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int is_prime(int num)
{
    if (num <= 1)
        return 0;
    for (int i = 2; i <= num / 2; i++)
        if (num % i == 0)
            return 0;
    return 1;
}

int main(int argc, char *argv[])
{
    int M, N;
    sscanf(argv[1], "%d", &M);
    sscanf(argv[2], "%d", &N);

    int shm_fd = shm_open("OS", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    void *ptr = mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sprintf(ptr, "The prime numbers between %d and %d are:\n", M, N);
    ptr += strlen((char *)ptr);

    for (int num = M; num <= N; num++)
    {
        if (is_prime(num))
        {
            sprintf(ptr, "%d\n", num);
            ptr += strlen((char *)ptr);
        }
    }

    return 0;
}
/*
!cc p.c -o parent -lrt
!cc c.c -o child -lrt
!./parent 2 10
*/