#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>

typedef struct 
{
    int n;
    int arr[100];
} pack_t;

int main()
{
    // Access existing shared memory
    int shmid = shmget((key_t)1122, sizeof(pack_t), 0666);
    if (shmid < 0)
    {
        perror("shmget failed");
        exit(1);
    }

    pack_t *ptr = (pack_t *)shmat(shmid, NULL, 0);
    if (ptr == (void *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    printf("Generating odd numbers:\n");
    for(int i = 0; i < ptr->n; i++)
    {
        ptr->arr[i] = 2 * i + 1;
        printf("%d ", ptr->arr[i]);
    }
    printf("\n");

    // Detach shared memory
    shmdt((void *)ptr);

    return 0;
}
