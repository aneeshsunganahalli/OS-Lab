#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t wrt;
int cnt = 1;
pthread_mutex_t mutex;
int readnumber = 0;

void *reader(void *rno)
{
  pthread_mutex_lock(&mutex);
  readnumber++;
  if (readnumber == 1)
    sem_wait(&wrt);
  printf("Reader &d read count as %d", *(int *)rno, cnt);
  pthread_mutex_unlock(&mutex);
  pthread_mutex_lock(&mutex);
  readnumber--;
  if (readnumber == 0)
    sem_post(&wrt);
  pthread_unlock_mutex(&mutex);
}

void *writer(void *wno)
{
  sem_wait(&wrt);
  cnt = cnt *2;
  printf("Wrote");
  sem_post(&wrt);
}

int main(){
  pthread read[3], write[3];
  sem_init(&wrt,0,1);
  pthread_mutex_init(&mutex, NULL);

  int a[3] = {1,2,3};
  for(int i = 0; i< 3; i++)
    pthread_create(&read, NULL, reader, (void *)&a[i]);

  for(int i = 0; i< 3; i++)
    pthread_create(&write, NULL, writer, (void *)&a[i]);

  for(int i = 0; i< 3; i++)
    pthread_join(read, NULL);
  for(int i = 0; i< 3; i++)
    pthread_join(write, NULL);
  
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}