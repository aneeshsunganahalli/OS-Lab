#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>

typedef struct
{
  int n;
  int arr[100];
} pack_t;

int main()
{
  key_t key = 1234;
  int shmid = shmget(key, sizeof(pack_t), 0666 | IPC_CREAT);
  pack_t * ptr = (pack_t *)shmat(shmid, NULL, 0666);

  printf("Enter n: ");
  scanf("%d", ptr->n);

  pid_t pid;
  pid = fork();

  if (pid == 0)
  {
    execlp("./child","child", NULL);
  }
  else if (pid > 0)
  {
    wait(NULL);
    for ( int i = 0; i < ptr->n; i++)
    {
      printf("%d ", ptr->arr[i]);
    }
  }

  shmdt((void *)ptr);
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}