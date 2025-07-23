#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define MaxItems 3
#define BufferSize 3

sem_t empty;
sem_t full;
pthread_mutex_t mutex;
int in = 0;
int out = 0;
int buffer[BufferSize];

void *producer(void *pno)
{
  int item;
  for (int i = 0; i < MaxItems; i++)
  {
    item = rand() % 100;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    buffer[in] = item;
    printf("Producer %d: Add %d at %d", *(int *)pno, buffer[in], in);
    in = (in + 1) % BufferSize;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
  }
}

void *consumer(void *cno)
{
  for (int i = 0; i < n; i++)
  {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    int item = buffer[out];
    printf("Consumer %d: Remove %d at %d", *(int *)cno, item, out);
    out = (out + 1) % BufferSize;
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
  }
}

int main()
{
  pthread_t pro[3], con[3];

  sem_init(&empty, 0, BufferSize);
  sem_init(&full, 0, 0);
  pthread_mutex_init(&mutex, NULL);
  int a[3] = {1, 2, 3};

  for (int i = 0; i < 3; i++)
    pthread_create(&pro[i], NULL, producer, (void *)&a[i]);

  for (int i = 0; i < 3; i++)
    pthread_create(&con[i], NULL, consumer, (void *)&a[i]);

  // Wait for all producer threads to complete
  for (int i = 0; i < 3; i++)
  {
    pthread_join(pro[i], NULL);
  }

  // Wait for all consumer threads to complete
  for (int i = 0; i < 3; i++)
  {
    pthread_join(con[i], NULL);
  }

  printf("\nAll threads completed successfully\n");

  // Cleanup
  pthread_mutex_destroy(&mutex);
  sem_destroy(&empty);
  sem_destroy(&full);

  return 0;
}