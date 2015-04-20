
/*
T1 SisOp Abril/2015
Fabio Galvao Rehm
Mateus Vendramini
*/

#ifndef MYMUTEX_H
#define MYMUTEX_H

typedef struct my_mutex_struct {
  int* level;
  int* waiting;
  int num_threads;
} my_mutex;

void m_init(my_mutex*, int const); /* mutex inst, num threads */
void m_free(my_mutex*); /* mutex inst */

void m_lock(my_mutex*, int const); /* mutex inst, thread id */
void m_unlock(my_mutex*, int const); /* mutex inst, thread id */

#endif

