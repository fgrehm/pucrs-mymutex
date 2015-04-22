#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include "mymutex.h"

#define PRODUCERS  3
#define CONSUMERS  3

int rc;
int wc;
/*my_mutex mutex_rc;
my_mutex mutex_wc;
my_mutex mutex;
my_mutex w_db;
my_mutex r_db;*/

sem_t mutex_rc;
sem_t mutex_wc;
sem_t mutex;
sem_t w_db;
sem_t r_db;

void do_work(int tid, char* thread_type, char* work) {
  printf("[%03d-%s] %s\n", tid, thread_type, work);
  int s = random() % 2 + 1;
  sleep(s);
  printf("[%03d-%s] Fim\n", tid, thread_type);
}

// WRITER
void *producer(void *arg){
  int tid = (int)(long int)arg;

  while (1){

    //down(mutex_wc);
    //m_lock(&mutex_wc, 1);
    sem_wait(&mutex_wc);

    wc++;

    if (wc == 1){
      //down(r_db);
      //m_lock(&r_db, 1);
      sem_wait(&r_db);
    }

    //up(mutex_wc);
    //m_unlock(&mutex_rc, 1);
    sem_post(&mutex_rc);

    //down(w_db)
    //m_lock(&w_db, 1);
    sem_wait(&w_db);

    // TODO: escrita
    do_work(tid, "Produtor", "Escrevendo...");

    //up(w_db)
    //m_unlock(&w_db, 1);
    sem_post(&w_db);

    //down(mutex_wc);
    //m_lock(&mutex_wc, 1);
    sem_wait(&mutex_wc);

    wc--;
    if (wc == 0){
      //up(r_db);
      //m_unlock(&r_db, 1);
      sem_post(&r_db);
    }

    //up(mutex_wc);
    //m_unlock(&mutex_wc, 1);
    sem_post(&mutex_wc);

  }

}

// READER
void *consumer(void *arg){
  int tid = (int)(long int)arg;

  while (1){

    //down(mutex);
    //m_lock(&mutex, 1);
    sem_wait(&mutex);

    //down(r_db);
    //m_lock(&r_db, 1);
    sem_wait(&r_db);

    //down(mutex_rc);
    //m_lock(&mutex_rc, 1);
    sem_wait(&mutex_rc);

    rc++;

    if (rc == 1){
      //down(w_db);
      //m_lock(&w_db, 1);
      sem_wait(&w_db);
    }

    //up(mutex_rc);
    //m_unlock(&mutex_rc, 1);
    sem_post(&mutex_rc);

    //up(r_db);
    //m_unlock(&r_db, 1);
    sem_post(&r_db);

    //up(mutex);
    //m_unlock(&mutex, 1);
    sem_post(&mutex);

    // TODO: leitura
    do_work(tid, "Consumidor", "Lendo...");

    //down(mutex_rc);
    //m_lock(&mutex_rc, 1);
    sem_wait(&mutex_rc);

    rc--;

    if (rc == 0){
      //up(w_db);
      //m_unlock(&w_db, 1);
      sem_post(&w_db);
    }

    //up(mutex_rc);
    //m_unlock(&mutex_rc, 1);
    sem_post(&mutex_rc);

  }

}

int main(int argc, char *argv[]) {
  srandom(time(NULL));

  pthread_t producers[PRODUCERS], consumers[CONSUMERS];

  // INIT
  rc = 0;
  wc = 0;
  /*m_init(&mutex_rc, 1);
  m_init(&mutex_wc, 1);
  m_init(&mutex, 1);
  m_init(&w_db, 1);
  m_init(&r_db, 1);*/

  sem_init(&mutex_rc, 0, 1);
  sem_init(&mutex_wc, 0, 1);
  sem_init(&mutex, 0, 1);
  sem_init(&w_db, 0, 1);
  sem_init(&r_db, 0, 1);

  int i=0;
  for (i = 0; i < PRODUCERS; i++)
    pthread_create(&producers[i], NULL, producer, (void *)(intptr_t)i);
  for (i = 0; i < CONSUMERS; i++)
    pthread_create(&consumers[i], NULL, consumer, (void *)(intptr_t)i);

  pthread_exit(0);
  /*m_free(&mutex_rc);
  m_free(&mutex_wc);
  m_free(&mutex);
  m_free(&w_db);
  m_free(&r_db);*/

  return 0;
}

