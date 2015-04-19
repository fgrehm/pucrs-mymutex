
#ifndef MYMUTEX_H
#define MYMUTEX_H

void m_init(int const); /* num threads */
void m_exit();

void m_lock(int const); /* thread id */
void m_unlock(int const); /* thread id */

#endif

