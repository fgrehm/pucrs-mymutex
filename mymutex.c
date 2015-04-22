/*
T1 SisOp Abril/2015
Fabio Galvao Rehm
Mateus Vendramini
*/

#include <stdio.h>
#include <stdlib.h>
#include "mymutex.h"

#define ASSERT_VALID_TID(M,T) if (T >= 0 && T <= M->num_threads) { /* ok! */ } else { printf("invalid tid: [%d], max: [%d].\n", T, M->num_threads); return; }

void m_init(my_mutex *mu, int const num_threads) {
  // allocation
  mu->num_threads = num_threads;
  mu->tickets = (int*)calloc(num_threads, sizeof(int));
  mu->entering = (int*)calloc(num_threads, sizeof(int));

  // starting vals
  int i;
  for (i = 0; i < num_threads; ++i) {
    mu->tickets[i] = 0;
    mu->entering[i] = 0;
  }
}

void m_free(my_mutex *mu){
  // deallocation
  free(mu->entering);
  free(mu->tickets);
}

// Lamport's bakery algorithm
void m_lock(my_mutex *mu, int const tid) {
  ASSERT_VALID_TID(mu, tid);

  mu->entering[tid] = 1;
  int max = 0;
  int n;
  for (n = 0; n < mu->num_threads; n++) {
    if (mu->tickets[n] > max)
      max = n;
  }
  mu->tickets[tid] = 1 + max;
  mu->entering[tid] = 0;

  int i;
  for (i = 0; i < mu->num_threads; ++i) {
    if (i != tid) {
      while (mu->entering[i]) { /* wait while other thread picks a ticket */ }

      while (mu->tickets[i] != 0 && (mu->tickets[tid] > mu->tickets[i] || (mu->tickets[tid] == mu->tickets[i] && tid > i))) {
        /* wait for other threads that have a higher priority to finish */
      }
    }
  }
}

void m_unlock(my_mutex *mu, int const tid) {
  ASSERT_VALID_TID(mu, tid);

  mu->tickets[tid] = 0;
}
