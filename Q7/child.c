#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
  int n1, n2, n3, k = 2;
  void *ptr;
  int shmid = shmget((key_t)1122, 4096, 0666);
  ptr = shmat(shmid, NULL, 0);

  int i = atoi(argv[1]);
  n1 = 0;
  n2 = 1;

  // First number
  sprintf(ptr, "%d ", n1);
  ptr += strlen(ptr);

  // Second number
  sprintf(ptr, "%d ", n2);
  ptr += strlen(ptr);

  // Remaining numbers
  while (k < i)
  {
    n3 = n1 + n2;
    sprintf(ptr, "%d ", n3);
    ptr += strlen(ptr);
    n1 = n2;
    n2 = n3;
    k++;
  }

  shmdt(ptr);  // detach
  return 0;
}
