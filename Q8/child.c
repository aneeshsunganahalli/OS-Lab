#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  const char *name = "/VSS";
  const int SIZE = 4096;
  int shmfd;
  void *base;
  char *ptr;

  if (argc != 2)
  {
    printf("Usage: %s <num_terms>\n", argv[0]);
    return 1;
  }

  int n = atoi(argv[1]);
  int n1 = 0, n2 = 1, n3, k = 2;

  shmfd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shmfd, SIZE);
  base = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shmfd, 0);
  ptr = (char *)base;

  ptr += sprintf(ptr, "%d", n1);
  if (n > 1)
    ptr += sprintf(ptr, " %d", n2);

  while (k < n)
  {
    n3 = n1 + n2;
    ptr += sprintf(ptr, " %d", n3);
    n1 = n2;
    n2 = n3;
    k++;
  }

  *ptr = '\0'; // terminate string

  munmap(base, SIZE);
  close(shmfd);

  return 0;
}
