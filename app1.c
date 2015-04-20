#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include "mymutex.h"

#define NUM_THREADS 5
#define PRODUCERS  3
#define CONSUMERS  3

//sem_t mutex, empty, full;
my_mutex mutex, empty, full;
int in=0, out=0, buffer[NUM_THREADS];

void do_work(int tid, char* thread_type, char* work) {
  printf("[%03d-%s] %s\n", tid, thread_type, work);
  int s = random() % 2 + 1;
  sleep(s);
  printf("[%03d-%s] Fim\n", tid, thread_type);
}

void *producer(void *arg){
  int item, tid;

  tid = (int)(long int)arg;
  while(1){
    item=random();

    //sem_wait(&empty);      /* wait() ou p() ou down() */
    m_lock(&empty, tid);

    //sem_wait(&mutex);      /* wait() ou p() ou down() */
    m_lock(&mutex, 1);

    buffer[in]=item;
    char work[40];
    sprintf(work, "Escrevendo na pos %d", in);
    do_work(tid, "Produtor", work);
    in=(in+1)%NUM_THREADS;

    //sem_post(&mutex);      /* post() ou v() ou up() ou signal() */
    m_unlock(&mutex, 1);

    //sem_post(&full);      /* post() ou v() ou up() ou signal() */
    m_unlock(&full, tid);

  }
}

void *consumer(void *arg){
  int item, tid;

  tid = (int)(long int)arg;
  while(1){

    //sem_wait(&full);      /* wait() ou p() ou down() */
    m_lock(&full, tid);

    //sem_wait(&mutex);      /* wait() ou p() ou down() */
    m_lock(&mutex, 1);

    item=buffer[out];

    char work[40];
    sprintf(work, "Retirando da pos %d", in);
    do_work(tid, "Consumidor", work);
    out=(out+1)%NUM_THREADS;

    //sem_post(&mutex);      /* post() ou v() ou up() ou signal() */
    m_unlock(&mutex, 1);

    //sem_post(&empty);      /* post() ou v() ou up() ou signal() */
    m_unlock(&empty, tid);

    item=0;
  }
}

int main(int argc, char *argv[]){
  srandom(time(NULL));

  long int i;
  pthread_t producers[PRODUCERS], consumers[CONSUMERS];

  //sem_init(&mutex,0,1);
  m_init(&mutex, 1);
  //sem_init(&empty,0,NUM_THREADS);
  m_init(&empty, NUM_THREADS);
  //sem_init(&full,0,0);
  m_init(&full, NUM_THREADS);

  for(i = 0; i < PRODUCERS; i++)
    pthread_create(&producers[i], NULL, producer, (void *)i);
  for(i = 0; i < CONSUMERS; i++)
    pthread_create(&consumers[i], NULL, consumer, (void *)i);

  pthread_exit(0);
  m_free(&mutex);
  m_free(&empty);
  m_free(&full);
  return(0);
}

