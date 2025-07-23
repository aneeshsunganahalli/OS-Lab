#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
  int n1,n2,n3,k=2;
  int shmfd = shm_open("VSS", O_CREAT | O_RDWR, 0666);
  ftruncate(shmfd, 4096);
  void *ptr;
  ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shmfd, 0);
  int i = atoi(argv[1]);
  n1 = 0;
  n2 = 1;
  sprintf(ptr, "%d", n1);
  ptr += strlen(ptr);
  sprintf(ptr, "%d", n2);
  ptr += strlen(ptr);

  while (k != i)
  {
    n3 = n1 + n2;
    sprintf(ptr, "%d", n3);
    n1 = n2;
    n2 = n3;
    ptr += strlen(ptr);
    k++;
  }
}