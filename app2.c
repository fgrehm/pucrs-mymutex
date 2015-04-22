#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include "mymutex.h"

#define PRODUCERS  3
#define CONSUMERS  3

int rc;
int wc;
my_mutex mutex_rc;
my_mutex mutex_wc;
my_mutex mutex;
my_mutex w_db;
my_mutex r_db;

// WRITER
void *producer(void *arg){

  while (1){

    //down(mutex_wc);
    m_lock(&mutex_wc, 1);

    wc++;

    if (wc == 1){
      //down(r_db);
      m_lock(&r_db, 1);
    }

    //up(mutex_wc);
    m_unlock(&mutex_rc, 1);

    //down(w_db)
    m_lock(&w_db, 1);

    // TODO: escrita
    printf("escrevendo...\n");

    //up(w_db)
    m_unlock(&w_db, 1);

    //down(mutex_wc);
    m_lock(&mutex_wc, 1);

    wc--;
    if (wc == 0){
      //up(r_db);
      m_unlock(&r_db, 1);
    }

    //up(mutex_wc);
    m_unlock(&mutex_wc, 1);

  }

}

// READER
void *consumer(void *arg){

  while (1){

    //down(mutex);
    m_lock(&mutex, 1);

    //down(r_db);
    m_lock(&r_db, 1);

    //down(mutex_rc);
    m_lock(&mutex_rc, 1);

    rc++;

    if (rc == 1){
      //down(w_db);
      m_lock(&w_db, 1);
    }

    //up(mutex_rc);
    m_unlock(&mutex_rc, 1);

    //up(r_db);
    m_unlock(&r_db, 1);

    //up(mutex);
    m_unlock(&mutex, 1);

    // TODO: leitura
    printf("lendo...\n");

    //down(mutex_rc);
    m_lock(&mutex_rc, 1);

    rc--;

    if (rc == 0){
      //up(w_db);
      m_unlock(&w_db, 1);
    }

    //up(mutex_rc); 
    m_unlock(&mutex_rc, 1);

  }

}

int main(int argc, char *argv[]) {

  pthread_t producers[PRODUCERS], consumers[CONSUMERS];

  // INIT
  rc = 0;
  wc = 0;
  m_init(&mutex_rc, 1);
  m_init(&mutex_wc, 1);
  m_init(&mutex, 1);
  m_init(&w_db, 1);
  m_init(&r_db, 1);

  int i=0;
  for (i = 0; i < PRODUCERS; i++)
    pthread_create(&producers[i], NULL, producer, (void *)(intptr_t)i);
  for (i = 0; i < CONSUMERS; i++)
    pthread_create(&consumers[i], NULL, consumer, (void *)(intptr_t)i);

  pthread_exit(0);
  m_free(&mutex_rc);
  m_free(&mutex_wc);
  m_free(&mutex);
  m_free(&w_db);
  m_free(&r_db);

  return 0;
}

