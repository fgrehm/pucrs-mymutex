#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include "mymutex.h"

#define NUM_THREADS 5
#define NUM_PRINTS 300

void print(void* arg){

  int tid =  (intptr_t)arg;
  m_lock(tid);

  int i=0;
  for (i=0; i<NUM_PRINTS; ++i){
    printf("%d\n", i);
  }
  m_unlock(tid);
}

int main() {

  m_init(NUM_THREADS);
  pthread_t threads[NUM_THREADS];
  int i=0;
  for (i=0; i<NUM_THREADS; ++i){
    int rc = pthread_create(&threads[i], NULL, (void*)print, (void *) (intptr_t)i);
  }

  pthread_exit(0);
  m_exit();

  return 0;
}

