#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
#include <wait.h>

typedef struct
{
    int n;
    int arr[100];
} pack_t;

int main()
{
    int shmid;

    // Create shared memory
    shmid = shmget((key_t)1122, sizeof(pack_t), 0666 | IPC_CREAT);
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

    // Input number of elements
    printf("Enter n: ");
    scanf("%d", &ptr->n);

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) // Child process
    {
        execlp("./child", "child", NULL);
        perror("execlp failed");
        exit(1);
    }
    else // Parent process
    {
        wait(NULL); // Wait for child to complete

        printf("Parent printing generated numbers:\n");
        for (int i = 0; i < ptr->n; i++)
        {
            printf("%d ", ptr->arr[i]);
        }
        printf("\n");
    }

    // Detach and remove shared memory
    shmdt((void *)ptr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
