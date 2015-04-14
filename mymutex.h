#ifndef MYMUTEX_H
#define MYMUTEX_H

void init(int num_threads);
void lock(int tid);
void unlock(int tid);
#endif
