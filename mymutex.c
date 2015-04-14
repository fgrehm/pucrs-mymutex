#include <stdlib.h>

int* interested;

void init(int num_threads) {
  interested = (int*)calloc(num_threads, sizeof(int));
}

void lock(int tid) {
}

void unlock(int tid) {
}
