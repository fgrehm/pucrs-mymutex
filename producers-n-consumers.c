/*
T1 SisOp Abril/2015
Fabio Galvao Rehm
Mateus Vendramini
*/

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include "mymutex.h"

#define PRODUCERS  3
#define CONSUMERS  7
#define NUM_THREADS PRODUCERS+CONSUMERS
#define BUFFER_SIZE 5

sem_t empty, full;
my_mutex mutex;

int in=0, out=0, buffer[BUFFER_SIZE];

void do_work(char* process_type, int thread_id, char* work) {
  printf("[%s-%d] %s\n", process_type, thread_id, work);
  int r = random() % 2;
  sleep(r);
}

void *producer(void *arg){
  int item, tid;
  tid = (int)(long int)arg;

  while(1){
    do_work("PRODUCER", tid, "Generating item");
    item = random() % 100;

    sem_wait(&empty);

    m_lock(&mutex, tid);
    printf("[PRODUCER-%d] Writing '%d' at position '%d'\n", tid, item, in);
    buffer[in]=item;
    // Move in "pointer" to the next available slot
    in=(in+1)%BUFFER_SIZE;
    m_unlock(&mutex, tid);

    sem_post(&full);
  }
}

void *consumer(void *arg){
  int item, tid, old_out;

  tid = (int)(long int)arg;
  // This is needed since we spawn PRODUCERS threads before creating
  // reader threads
  tid += PRODUCERS;

  while(1){
    sem_wait(&full);

    m_lock(&mutex, tid);
    old_out = out;
    item=buffer[out];
    out=(out+1)%BUFFER_SIZE;
    m_unlock(&mutex, tid);

    char msg[50];
    sprintf(msg, "Consuming item from position '%d', value '%d'", old_out, item);
    do_work("CONSUMER", tid, msg);

    sem_post(&empty);
  }
}

int main(int argc, char *argv[]){
  srandom(time(NULL));

  long int i;
  pthread_t producers[PRODUCERS], consumers[CONSUMERS];

  m_init(&mutex, NUM_THREADS);
  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);

  for(i = 0; i < PRODUCERS; i++)
    pthread_create(&producers[i], NULL, producer, (void *)i);
  for(i = 0; i < CONSUMERS; i++)
    pthread_create(&consumers[i], NULL, consumer, (void *)i);

  pthread_exit(0);

  m_free(&mutex);

  return(0);
}
