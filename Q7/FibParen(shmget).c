#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  int i;
  void *ptr;
  int shmid = shmget((key_t)1122, 4096, 0666 | IPC_CREAT);
  ptr = shmat(shmid, NULL, 0);

  if (argc == 2)
  {
    sscanf(argv[1], "%d", &i);
    if (i < 1)
    {
      printf("Error input: %d\n", i);
      return 0;
    }
  }
  else if (argc > 2)
  {
    printf("Too many arguments\n");
    return 1;
  }
  else
  {
    printf("Invalid input format\n");
    return 1;
  }

  pid_t pid;
  pid = fork();
  if (pid == 0)
  {
    execlp("./child", "child", argv[1], NULL);
    perror("execlp failed");
    exit(1);
  }
  else if (pid > 0)
  {
    wait(NULL);
    printf("\nPARENT: child completed\n");
    printf("Parent printing Fibonacci series:\n");
    printf("%s\n", (char *)ptr);

    shmdt(ptr);                 // detach
    shmctl(shmid, IPC_RMID, 0); // remove shared memory
  }
  else
  {
    perror("fork failed");
    return 1;
  }

  return 0;
}
