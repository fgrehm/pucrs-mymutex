#include <stdlib.h>

int turn;
int* interested = 0;

void init(int num_threads) {
  interested = (int*)calloc(num_threads, sizeof(int));
}

void deinit() {
  if (interested)
    free(interested);
}

void lock(int mutex_id) {
  int other;

  other = 1 - mutex_id;
  interested[mutex_id] = 1;
  turn = mutex_id;
  while(turn == mutex_id && interested[other] == 1);
}

void unlock(int mutex_id) {
}
