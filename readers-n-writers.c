/*
T1 SisOp Abril/2015
Fabio Galvao Rehm
Mateus Vendramini
*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include "mymutex.h"

#define READERS 5
#define WRITERS 2
#define NUM_THREADS READERS+WRITERS

int rc = 0, wc = 0;
my_mutex mutex_rc, mutex_wc, mutex;
sem_t w_db, r_db;

void do_work(char* process_type, int thread_id, char* work, int min_wait) {
  printf("[%s-%d] %s\n", process_type, thread_id, work);
  float r = random() % 2 + min_wait;
  sleep(r);
}

void *writer(void* arg) {
  int wid = (int)(long int)arg;
  int tid = wid;

  while (1) {
    do_work("WRITER", wid, "Preparing to write", 2);
    printf("[WRITER-%d] Done with preparation\n", wid);

    m_lock(&mutex_wc, tid);
    wc++;
    if (wc == 1)
      sem_wait(&r_db);
    m_unlock(&mutex_wc, tid);
    sem_wait(&w_db);

    do_work("WRITER", wid, "Writing to DB", 2);
    printf("[WRITER-%d] Done writing\n", wid);

    sem_post(&w_db);
    m_lock(&mutex_wc, tid);
    wc--;
    if(wc == 0)
      sem_post(&r_db);
    m_unlock(&mutex_wc, tid);
  }
}

void *reader(void* arg) {
  int rid = (int)(long int)arg;
  int tid = rid + WRITERS;

  while (1) {
    m_lock(&mutex, tid);
    sem_wait(&r_db);
    m_lock(&mutex_rc, tid);
    rc++;
    if (rc == 1)
      sem_wait(&w_db);
    m_unlock(&mutex_rc, tid);
    sem_post(&r_db);
    m_unlock(&mutex, tid);

    do_work("READER", rid, "Reading from DB", 1);
    printf("[READER-%d] Done reading\n", rid);

    m_lock(&mutex_rc, tid);
    rc--;
    if (rc == 0)
      sem_post(&w_db);
    m_unlock(&mutex_rc, tid);

    do_work("READER", rid, "Using DB data", 0);
  }
}

int main() {
  srandom(time(NULL));

  pthread_t writer_workers[WRITERS];
  pthread_t reader_workers[READERS];
  long int i;

  m_init(&mutex_rc, NUM_THREADS);
  m_init(&mutex_wc, NUM_THREADS);
  m_init(&mutex, NUM_THREADS);
  sem_init(&w_db, 0, 1);
  sem_init(&r_db, 0, 1);

  for (i = 0; i < WRITERS; i++)
    pthread_create(&writer_workers[i], NULL, writer, (void *)i);
  for (i = 0; i < READERS; i++)
    pthread_create(&reader_workers[i], NULL, reader, (void *)i);

  pthread_exit(0);

  m_free(&mutex_rc);
  m_free(&mutex_wc);
  m_free(&mutex);

  return 0;
}
