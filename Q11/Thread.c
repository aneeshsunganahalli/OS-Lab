#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *add(void *arg)
{
  int n = *(int *)arg;
  int sum = 0;
  for(int i = 0; i<n; i++)
    sum += i
  printf("Sum: %d",sum);
  pthread_exit(NULL);
}

void *factorial(void *arg)
{
  int n = *(int *)arg;
  fact = 1;
  for(int i = 0; i < n; i++)
  {
    fact *= i;
  }
  printf("Factorial: %d", fact);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Improper Number of arguments");
    return 1;
  }

  pthread_t thread1, thread2;
  int n = atoi(argv[1]);

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&thread1, &attr, add, &n);
  pthread_create(&thread1, &attr, factorial, &n);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  return 0;
}