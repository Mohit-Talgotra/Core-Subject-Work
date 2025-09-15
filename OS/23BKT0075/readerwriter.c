#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//Mohit Talgotra 23BKT0075

sem_t mutex, wrt;
int readcount = 0, data = 0;

void *reader(void *arg)
{
    int id = *((int*)arg);
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
    {
        sem_wait(&wrt);
    }
    sem_post(&mutex);
    printf("Reader %d read data %d\n", id, data);
    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
    {
        sem_post(&wrt);
    }
    sem_post(&mutex);
    return NULL;
}

void *writer(void *arg)
{
    int id = *((int*)arg);
    sem_wait(&wrt);
    data++;
    printf("Writer %d wrote data %d\n", id, data);
    sem_post(&wrt);
    return NULL;
}

int main()
{
    pthread_t r[3], w[2];
    int id1 = 1, id2 = 2, id3 = 3, id4 = 1, id5 = 2;
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    pthread_create(&r[0], NULL, reader, &id1);
    pthread_create(&w[0], NULL, writer, &id4);
    pthread_create(&r[1], NULL, reader, &id2);
    pthread_create(&w[1], NULL, writer, &id5);
    pthread_create(&r[2], NULL, reader, &id3);
    for (int i = 0; i < 3; i++) pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL);
    return 0;
}
