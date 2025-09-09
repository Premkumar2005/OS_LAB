// parent.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
//  shm_open and mmap
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int shm_fd;
    void *ptr;
    const int SIZE = 4096;

    pid_t pid = fork();
    if (pid == 0)
    {
        execlp("./fib", "./fib", argv[1], NULL);
        perror("execlp");
        exit(1);
    }

    wait(NULL);
    shm_fd = shm_open("VSS", O_RDONLY, 0666);
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    printf("Fibonacci Series:\n%s\n", (char *)ptr);
    shm_unlink("VSS");
    return 0;
}

// gcc parent.c -o parent -lrt
// gcc fib.c -o fib -lrt
// ./parent 6
