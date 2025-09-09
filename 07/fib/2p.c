#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
//  using shmget and shmat
int main(int argc, char *argv[])
{
    int i;
    pid_t pid;
    void *ptr;
    int shmid;

    if (argc > 1)
    {
        sscanf(argv[1], "%d", &i);
        if (i < 1)
        {
            printf("Error input: %d\n", i);
            return 0;
        }
    }
    else
    {
        printf("Error: Not passing N in command line\n");
        return 1;
    }

    // Create shared memory with key 1122
    shmid = shmget((key_t)1122, 4096, 0666 | IPC_CREAT);
    ptr = shmat(shmid, NULL, 0);

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
        printf("\nPARENT: child completed\n");
        printf("Parent printing:\n");
        printf("%s\n", (char *)ptr);
        shmdt(ptr);
    }

    return 0;
}
