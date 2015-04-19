#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "mymutex.h"

#define NUM_THREADS 5
#define MULTIPLIER 200

/*my_mutex mutexes[NUM_THREADS-1];

void *print_numbers(void* arg) {
  int tid = (int)(long int)arg;
  int begin = tid * MULTIPLIER + 1;
  int end = (tid + 1) * MULTIPLIER;

  if (tid > 0) {
    m_lock(&mutexes[tid-1], tid);
  }

  int i;
  for (i = begin; i <= end; i++) {
    printf("[%d] %04d\n", tid, i);
  }

  if (tid < NUM_THREADS-1) {
    m_unlock(&mutexes[tid], tid);
  }
}*/

int main() {
  printf("spike?\n");
  m_init(NUM_THREADS);
/*  long int i;
  for (i = 0; i < NUM_THREADS-1; i++) {
    m_init(&mutexes[i], NUM_THREADS);
    m_lock(&mutexes[i], i);
  }

  pthread_t printers[NUM_THREADS];
  for (i = 0; i < NUM_THREADS; i++) {
    pthread_create(&printers[i], NULL, print_numbers, (void *)i);
  }

  pthread_exit(0);*/

  m_exit();
  return 0;
}

