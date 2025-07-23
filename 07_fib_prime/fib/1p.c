// parent.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/wait.h>
//  shm_open and mmap
int main(int argc, char *argv[])
{
    pid_t pid;
    int n;
    int shm_fd;
    const int SIZE = 4096;
    void *ptr;

    if (argc != 2)
    {
        printf("Error: Not passing N in command line\n");
        exit(1);
    }

    sscanf(argv[1], "%d", &n);
    if (n < 1)
    {
        printf("Error input %d\n", n);
        return 0;
    }

    pid = fork();
    if (pid == 0)
    {
        execlp("./fib", "./fib", argv[1], NULL);
        perror("execlp failed");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("PARENT child completed\n");
        shm_fd = shm_open("VSS", O_RDONLY, 0666);
        if (shm_fd == -1)
        {
            perror("shm_open failed in parent");
            exit(1);
        }
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        printf("Parent printing\n");
        printf("%s\n", (char *)ptr);
        shm_unlink("VSS");
    }

    return 0;
}
