#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int n;
  int arr[100];
} pack_t;

int main(int argc, char *argv[])
{
  key_t key = 1234;
  int shmid = shmget(key, sizeof(pack_t), 0666);
  pack_t *ptr = (pack_t *)shmat(shmid, NULL, 0666);

  printf("Child: Generating %d odd numbers: ", ptr->n);
  for (int i = 0; i < n; i++)
  {
    ptr->arr[i] = 2 * i + 1;
  }
  shmdt((void *)ptr);
  return 0;
}