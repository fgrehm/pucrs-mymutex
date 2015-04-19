#include <stdio.h>
#include <stdlib.h>
#include "mymutex.h"

struct my_mutex_struct {
  int* level;
  int* waiting;
} my_mutex;


int m_is_inited = 0;
int m_num_threads = 0;

void m_init(const int num_threads) {

  if (m_is_inited){
    printf("mymutex has already been initialised.\n");
    return;
  }

  m->level = calloc(max_num_threads, sizeof(int));
  m->waiting = calloc(max_num_threads, sizeof(int));
  m_num_threads = num_threads;

  int i;
  for (i = 0; i < max_num_threads; ++i) {
    m->level[i] = -1;
  }

  m_is_inited = 1;

}

void m_exit(){
  if (!m_is_inited){
    printf("mymutex has not been initialised.\n");
    return;
  }
  // TODO: freedom !!
}

void m_lock(const int tid) {
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

void m_unlock(const int tid) {
  m->level[tid] = -1;
}

