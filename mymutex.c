#include <stdio.h>
#include <stdlib.h>
#include "mymutex.h"

typedef struct my_mutex_struct {
  int* level;
  int* waiting;
} my_mutex;


int m_is_inited = 0;
int m_num_threads = 0;
my_mutex mu;

#define ASSERT_VALID_TID(A) if (A >= 0 && A < m_num_threads) { /* ok! */ } else { printf("invalid tid.\n"); return; }

void m_init(int const num_threads) {

  // initialisation sentinel
  if (m_is_inited){
    printf("mymutex has already been initialised.\n");
    return;
  }

  // allocation
  m_num_threads = num_threads;
  mu.level = (int*)calloc(m_num_threads, sizeof(int));
  mu.waiting = (int*)calloc(m_num_threads, sizeof(int));

  // starting vals
  int i;
  for (i = 0; i < m_num_threads; ++i) {
    mu.level[i] = -1;
  }

  // we are up
  m_is_inited = 1;

}

void m_exit(){

  // must have initialised to exit
  if (!m_is_inited){
    printf("mymutex has not been initialised.\n");
    return;
  }

  // deallocation
  free(mu.level);
  free(mu.waiting);

}

void m_lock(int const tid) {

  ASSERT_VALID_TID(tid);

  // peterson's generalised algorithm for N threads/processes
  int i=0;
  int j=0;
  for (i=0; i<m_num_threads-1; ++i){
    mu.level[tid] = i; 
    mu.waiting[i] = tid;
    for (j=0; j<m_num_threads; ++j){
      while (j != tid && mu.level[j] >= i && mu.waiting[i] == tid);
    }
  }

}

void m_unlock(int const tid) {

  ASSERT_VALID_TID(tid);

  mu.level[tid] = -1; // unlock this "waiting room"

}

