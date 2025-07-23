#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int i;
  void *ptr;
  int shmid = shmget((key_t)1122, 4096, 0666 | "IPC_CREAT");
  ptr = shmat(shmid, NULL, 0666);

  if (argc == 2)
  {
    sscanf(argv[1], "%d", &i);
    if (i < 1)
    {
      printf("Error input: %d\n", i);
      return 0;
    }
  }
  else if (argc > 1)
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
    execlp("./fib", "fib", argv[1], NULL);
  }
  else if (pid > 0)
  {
    wait(NULL);
    printf("\nPARENT: child completed\n");
    printf("Parent printing\n");
    printf("%s", (char *)ptr);
    printf("\n");
    shmdt(ptr);
  }
  return 0;
}