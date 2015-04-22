#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define READERS 5
#define WRITERS 2

int rc = 0;
sem_t write_lock, rc_mutex;

void do_work(char* process_type, int thread_id, char* work, int min_wait) {
  printf("[%s-%d] %s\n", process_type, thread_id, work);
  float r = random() % 2 + 1;
  sleep(r);
}

void *writer(void* arg) {
  int wid = (int)(long int)arg;

  while (1) {
    do_work("WRITER", wid, "Preparing data to be written", 1);
    sem_wait(&write_lock);
    do_work("WRITER", wid, "Writing to DB", 2);
    sem_post(&write_lock);
  }
}

void *reader(void* arg) {
  int rid = (int)(long int)arg;

  while (1) {
    sem_wait(&rc_mutex);
    rc++;
    if (rc == 1) {
      sem_wait(&write_lock);
    }
    sem_post(&rc_mutex);

    do_work("READER", rid, "Reading from DB", 1);

    sem_wait(&rc_mutex);
    rc--;
    if (rc == 0) {
      sem_post(&write_lock);
    }
    sem_post(&rc_mutex);

    do_work("READER", rid, "Using DB data", 2);
  }
}

int main() {
  srandom(time(NULL));

  pthread_t writer_workers[WRITERS];
  pthread_t reader_workers[READERS];
  long int i;

  sem_init(&write_lock, 0, 1);
  sem_init(&rc_mutex, 0, 1);

  for (i = 0; i < WRITERS; i++) {
    pthread_create(&writer_workers[i], NULL, writer, (void *)i);
  }

  for (i = 0; i < READERS; i++) {
    pthread_create(&reader_workers[i], NULL, reader, (void *)i);
  }

  pthread_exit(0);
  return 0;
}
