#ifndef MYMUTEX_H
#define MYMUTEX_H

void init(int num_threads);
void lock(int mutex_id);
void unlock(int mutex_id);
#endif
