#ifndef MYMUTEX_H
#define MYMUTEX_H

typedef struct my_mutex_struct {
  int* level;
  int* waiting;
  int max_num_threads;
  int mutex_id;
} my_mutex;

void m_init(my_mutex*, int);
void m_lock(my_mutex*, int);
void m_unlock(my_mutex*, int);
#endif
