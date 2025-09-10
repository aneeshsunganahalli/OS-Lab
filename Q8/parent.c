#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
  const char *name = "/VSS";   // shared memory name
  const int SIZE = 4096;
  void *ptr;
  int shm_fd;
  pid_t pid;

  if (argc != 2)
  {
    printf("Usage: %s <num_terms>\n", argv[0]);
    return 1;
  }

  pid = fork();
  if (pid == 0)
  {
    execlp("./child", "child", argv[1], NULL);
    exit(1); // in case execlp fails
  }
  else
  {
    wait(NULL); // wait for child

    shm_fd = shm_open(name, O_RDONLY, 0666);
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    printf("\nPARENT: Child completed\n");
    printf("Parent printing\n");
    printf("%s\n", (char *)ptr);

    munmap(ptr, SIZE);
    close(shm_fd);
    shm_unlink(name);
  }

  return 0;
}
