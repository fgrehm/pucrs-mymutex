#include <stdio.h>
#include <stdlib.h>
#include "mymutex.h"

// TODO: Can we avoid the need for max_num_threads?
void m_init(my_mutex *m, int max_num_threads) {
  m->level = calloc(max_num_threads, sizeof(int));
  m->waiting = calloc(max_num_threads, sizeof(int));
  m->max_num_threads = max_num_threads;

  int i;
  for (i = 0; i < max_num_threads; ++i) {
    m->level[i] = -1;
  }
}

void m_lock(my_mutex *m, int tid) {
  // TODO: Attempt to make things transparent to the caller and avoid the
  //       need to have tid around
  // int tid = (int)(unsigned int)pthread_self();
  int l, k;

  for(l = 0; l < m->max_num_threads-1; ++l) {
    m->level[tid] = l;
    m->waiting[l] = tid;
    for (k = 0; k < m->max_num_threads; k++) {
      // there exists k != i, such that level[k] >= l
      while(k != tid && m->level[k] >= l && m->waiting[l] == tid);
    }
  }
}

void m_unlock(my_mutex *m, int tid) {
  m->level[tid] = -1;
}
