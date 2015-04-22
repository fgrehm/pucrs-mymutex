#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define READERS 7
#define WRITERS 2

int rc = 0, wc = 0;
sem_t mutex_rc, mutex_wc, mutex, w_db, r_db;

void do_work(char* process_type, int thread_id, char* work, int min_wait) {
  printf("[%s-%d] %s\n", process_type, thread_id, work);
  float r = random() % 2 + min_wait;
  sleep(r);
}

void *writer(void* arg) {
  int wid = (int)(long int)arg;

  while (1) {
    do_work("WRITER", wid, "Preparing to write", 0);
    printf("[WRITER-%d] Done with preparation\n", wid);

    sem_wait(&mutex_wc);
    wc++;
    if (wc == 1)
      sem_wait(&r_db);
    sem_post(&mutex_wc);
    sem_wait(&w_db);

    do_work("WRITER", wid, "Writing to DB", 1);
    printf("[WRITER-%d] Done writing\n", wid);

    sem_post(&w_db);
    sem_wait(&mutex_wc);
    wc--;
    if(wc == 0)
      sem_post(&r_db);
    sem_post(&mutex_wc);
  }
}

void *reader(void* arg) {
  int rid = (int)(long int)arg;

  while (1) {
    sem_wait(&mutex);
    sem_wait(&r_db);
    sem_wait(&mutex_rc);
    rc++;
    if (rc == 1)
      sem_wait(&w_db);
    sem_post(&mutex_rc);
    sem_post(&r_db);
    sem_post(&mutex);

    do_work("READER", rid, "Reading from DB", 1);
    printf("[READER-%d] Done reading\n", rid);

    sem_wait(&mutex_rc);
    rc--;
    if (rc == 0)
      sem_post(&w_db);
    sem_post(&mutex_rc);

    do_work("READER", rid, "Using DB data", 0);
  }
}

int main() {
  srandom(time(NULL));

  pthread_t writer_workers[WRITERS];
  pthread_t reader_workers[READERS];
  long int i;

  sem_init(&mutex_rc, 0, 1);
  sem_init(&mutex_wc, 0, 1);
  sem_init(&mutex, 0, 1);
  sem_init(&w_db, 0, 1);
  sem_init(&r_db, 0, 1);

  for (i = 0; i < WRITERS; i++) {
    pthread_create(&writer_workers[i], NULL, writer, (void *)i);
  }

  for (i = 0; i < READERS; i++) {
    pthread_create(&reader_workers[i], NULL, reader, (void *)i);
  }

  pthread_exit(0);
  return 0;
}
