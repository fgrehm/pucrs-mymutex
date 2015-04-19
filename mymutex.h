
#ifndef MYMUTEX_H
#define MYMUTEX_H

void m_init(const int); /* num threads */
void m_exit();

void m_lock(const int); /* thread id */
void m_unlock(const int); /* thread id */

#endif

