#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "mymutex.h"

#define NUM_PROCS 5
#define MULTIPLIER 200

sem_t semaphores[NUM_PROCS-1];

void *print_numbers(void* arg) {
  int tid = (int)(long int)arg;
  int begin = tid * MULTIPLIER + 1;
  int end = (tid + 1) * MULTIPLIER;

  if (tid > 0) {
    sem_wait(&semaphores[tid-1]);
  }

  int i;
  for (i = begin; i <= end; i++) {
    printf("[%d] %04d\n", tid+1, i);
  }

  if (tid < NUM_PROCS-1) {
    sem_post(&semaphores[tid]);
  }
}

int main() {
  long int i;
  for (i = 0; i < NUM_PROCS-1; i++) {
    sem_init(&semaphores[i], 0, 0);
  }

  pthread_t printers[NUM_PROCS];
  for (i = 0; i < NUM_PROCS; i++) {
    pthread_create(&printers[i], NULL, print_numbers, (void *)i);
  }

  pthread_exit(0);
  return 0;
}
