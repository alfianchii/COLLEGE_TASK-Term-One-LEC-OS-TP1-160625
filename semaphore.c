#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopstick[N];

void *philosopher(void *arg);
void think(int id);
void eat(int id);
void take_chopsticks(int id);
void put_chopsticks(int id);

int main() {
  pthread_t thread_id[N];

  for (int i = 0; i < N; i++) {
    sem_init(&chopstick[i], 0, 1);
  }

  for (int i = 0; i < N; i++) {
    pthread_create(&thread_id[i], NULL, philosopher, (void *)(intptr_t)i);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(thread_id[i], NULL);
  }

  for (int i = 0; i < N; i++) {
    sem_destroy(&chopstick[i]);
  }

  return 0;
}

void *philosopher(void *arg) {
  int id = (intptr_t)arg;

  while (1) {
    think(id);
    take_chopsticks(id);
    eat(id);
    put_chopsticks(id);
  }
}

void think(int id) {
  printf("Philosopher %d is thinking.\n", id);
  sleep(1);
}

void eat(int id) {
  printf("Philosopher %d is eating.\n", id);
  sleep(1);
}

void take_chopsticks(int id) {
  int left = id;
  int right = (id + 1) % N;

  if (id % 2 == 0) {
    sem_wait(&chopstick[left]);
    sem_wait(&chopstick[right]);
  } else {
    sem_wait(&chopstick[right]);
    sem_wait(&chopstick[left]);
  }
}

void put_chopsticks(int id) {
  int left = id;
  int right = (id + 1) % N;

  sem_post(&chopstick[left]);
  sem_post(&chopstick[right]);
}