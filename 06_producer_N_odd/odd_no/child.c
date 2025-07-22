#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

typedef struct
{
    int n;
    int arr[100];
} pack_t;

int main()
{
    key_t key = 1234;
    int shmid = shmget(key, sizeof(pack_t), 0666);
    pack_t *shm_ptr = (pack_t *)shmat(shmid, NULL, 0666);

    printf("[CHILD] Attached to shared memory with key = %d, id = %d. address = %p\n", key, shmid, shm_ptr);

    for (int i = 0; i < shm_ptr->n; i++)
        shm_ptr->arr[i] = 2 * i + 1;

    printf("[CHILD] Finished generating first %d odd numbers\n", shm_ptr->n);
    shmdt((void *)shm_ptr); // Detach shared memory

    return 0;
}
/*!cc code.c
!cc cons.c -o child
!./a.out

[PARENT] Created shared memory with key = 1234, id = 1, address = 0x7d6f2141e000
[PARENT] Enter n: 10
[CHILD] Attached to shared memory with key = 1234, id = 1. address = 0x7d1a06fa7000
[CHILD] Finished generating first 10 odd numbers
[PARENT] Child finished executing.
[PARENT] The first 10 odd numbers are:
1 3 5 7 9 11 13 15 17 19
[PARENT] Shared Memory Deleted*/