#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 5

//Mohit Talgotra 23BKT0075

sem_t forks[N];

void *philosopher(void *arg)
{
    int id = *((int*)arg);
    int left = id;
    int right = (id + 1) % N;
    for (int i = 0; i < 2; i++)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        printf("Philosopher %d is eating\n", id);
        sleep(1);
        sem_post(&forks[right]);
        sem_post(&forks[left]);
        printf("Philosopher %d finished eating\n", id);
    }
    return NULL;
}

int main()
{
    pthread_t phil[N];
    int ids[N];
    for (int i = 0; i < N; i++)
    {
        sem_init(&forks[i], 0, 1);
        ids[i] = i;
    }
    for (int i = 0; i < N; i++)
    {
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++)
    {
        pthread_join(phil[i], NULL);
    }
    return 0;
}