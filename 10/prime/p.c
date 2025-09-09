#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int M, N;
    if (argc != 3)
    {
        printf("Error: Minimum of two arguments must be passed on command line arguments\n");
        exit(1);
    }

    sscanf(argv[1], "%d", &M);
    sscanf(argv[2], "%d", &N);
    if (M > N)
    {
        printf("Error input %d > %d\n", M, N);
        return 0;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        execl("./child", "child", argv[1], argv[2], NULL);
        perror("execl failed");
        exit(1);
    }
    else
    {
        wait(NULL);
        printf("PARENT: child completed\n");

        int shm_fd = shm_open("OS", O_RDONLY, 0666);
        struct stat statbuf;
        fstat(shm_fd, &statbuf);
        void *ptr = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, shm_fd, 0);
        close(shm_fd);

        printf("Parent printing:\n");
        printf("%s\n", (char *)ptr);
        shm_unlink("OS");
    }

    return 0;
}
