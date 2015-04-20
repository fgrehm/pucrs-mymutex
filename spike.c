#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include "mymutex.h"

#define NUM_THREADS 5
#define NUM_PRINTS 300

my_mutex mu;

void print(void* arg){

  int tid =  (intptr_t)arg;
  m_lock(&mu, tid);

  int i=0;
  for (i=0; i<NUM_PRINTS; ++i){
    printf("%d\n", i);
  }
  m_unlock(&mu, tid);

}

int main(int argc, char *argv[]) {

  m_init(&mu, NUM_THREADS);
  pthread_t threads[NUM_THREADS];
  int i=0;
  for (i=0; i<NUM_THREADS; ++i){
    int rc = pthread_create(&threads[i], NULL, (void*)print, (void *) (intptr_t)i);
    if (rc != 0){
      printf("failed creating threads.\n");
      return 1;
    }
  }

  pthread_exit(0);
  m_free(&mu);

  return 0;
}

