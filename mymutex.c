#include <stdio.h>
#include <stdlib.h>
#include "mymutex.h"

#define ASSERT_VALID_TID(M,T) if (T >= 0 && T <= M->num_threads) { /* ok! */ } else { printf("invalid tid: [%d].\n", T); return; }

void m_init(my_mutex *mu, int const num_threads) {

  // allocation
  mu->num_threads = num_threads;
  mu->level = (int*)calloc(num_threads, sizeof(int));
  mu->waiting = (int*)calloc(num_threads, sizeof(int));

  // starting vals
  int i;
  for (i = 0; i < num_threads; ++i) {
    mu->level[i] = -1;
  }

}

void m_free(my_mutex *mu){

  // deallocation
  free(mu->level);
  free(mu->waiting);

}

void m_lock(my_mutex *mu, int const tid) {

  ASSERT_VALID_TID(mu, tid);

  // peterson's generalised algorithm for N threads/processes
  int i=0;
  int j=0;
  for (i=0; i<mu->num_threads-1; ++i){
    mu->level[tid] = i;
    mu->waiting[i] = tid;
    for (j=0; j<mu->num_threads; ++j){
      while (j != tid && mu->level[j] >= i && mu->waiting[i] == tid);
    }
  }

}

void m_unlock(my_mutex *mu, int const tid) {

  ASSERT_VALID_TID(mu, tid);

  mu->level[tid] = -1; // unlock this "waiting room"

}

