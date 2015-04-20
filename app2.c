#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include "mymutex.h"

#define NUM_THREADS 5
#define NUM_PRINTS 300

/*

// DECL
rc
wc
mutex_rc
mutex_wc
mutex
w_db
r_db

// INIT
rc = 0
wc = 0
mutex_rc = 1
mutex_wc = 1
mutex = 1
w_db = 1
r_db = 1

// WRITER
while (TRUE){
down(mutex_wc);
wc++;
if (wc == 1)
down(r_db);
up(mutex_wc);
down(w_db)
...
//Escrita
...
up(w_db)
down(mutex_wc);
wc--;
if (wc == 0)
up(r_db);
up(mutex_wc);
}

// READER
while (TRUE){
down(mutex);
down(r_db);
down(mutex_rc);
rc++;
if (rc == 1)
down(w_db);
up(mutex_rc);
up(r_db);
up(mutex);
...
//Leitura dos dados
...
down(mutex_rc);
rc--;
if (rc == 0)
up(w_db);
up(mutex_rc); )

*/

/*
void print(void* arg){

  int tid =  (intptr_t)arg;
  m_lock(tid);

  int i=0;
  for (i=0; i<NUM_PRINTS; ++i){
    printf("%d\n", i);
  }
  m_unlock(tid);
}
*/

int main() {
/*
  m_init(NUM_THREADS);
  pthread_t threads[NUM_THREADS];
  int i=0;
  for (i=0; i<NUM_THREADS; ++i){
    int rc = pthread_create(&threads[i], NULL, (void*)print, (void *) (intptr_t)i);
  }

  pthread_exit(0);
  m_exit();
*/
  return 0;
}

