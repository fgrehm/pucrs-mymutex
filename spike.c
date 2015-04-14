#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "mymutex.h"

#define NUM_PROCS 5
#define MULTIPLIER 200

my_mutex mutexes[NUM_PROCS-1];

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

  if (tid < NUM_PROCS-1) {
    m_unlock(&mutexes[tid], tid);
  }
}

int main() {
  long int i;
  for (i = 0; i < NUM_PROCS-1; i++) {
    m_init(&mutexes[i], NUM_PROCS);
    m_lock(&mutexes[i], i);
  }

  pthread_t printers[NUM_PROCS];
  for (i = 0; i < NUM_PROCS; i++) {
    pthread_create(&printers[i], NULL, print_numbers, (void *)i);
  }

  pthread_exit(0);
  return 0;
}
