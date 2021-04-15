#include <pthread.h>
#include <cstdio>
#include <semaphore.h>
#include <unistd.h>

#define M 10 // number of writers
#define N 10 // number of readers
#define ITER 10 // iterations number
#define SLEEP_TIME 0 // threads sleep time

sem_t data_access, readers_counter_access; // sem.
unsigned int readers_count = 0;	// number of readers accessing the resource
pthread_t some_data = nullptr;

void *reader(void *params) {
    pthread_t thread_index = pthread_self();

    for (int i = 0; i < ITER; ++i) {
        sem_wait(&readers_counter_access);				 // We will manipulate the readers counter
        if (readers_count == 0)				// If there are currently no readers (we came first)...
            sem_wait(&data_access);				// ...requests exclusive access to the resource for readers

        readers_count++;							 // Note that there is now one more reader
        sem_post(&readers_counter_access);				 // We are done accessing the number of readers for now

        printf("Reader №%llu read about epic person: %llu! Iteration count: %d\n", thread_index, some_data, i);
        sleep(SLEEP_TIME);

        sem_wait(&readers_counter_access);				 // We will manipulate the readers counter
        readers_count--;							 // We are leaving, there is one less reader
        if (readers_count == 0)				// If there are no more readers currently reading...
            sem_post(&data_access);				// ...release exclusive access to the resource

        sem_post(&readers_counter_access);				 // We are done accessing the number of readers for now
    }
}

void *writer(void *params) {
    pthread_t thread_index = pthread_self();

    for (int i = 0; i < ITER; ++i) {
        sem_wait(&data_access);					// Request exclusive access to the resource

        printf("Writer №%llu writes himself in history! Iteration count: %d\n", thread_index, i);
        some_data = thread_index;

        sleep(SLEEP_TIME);
        sem_post(&data_access);					// Release exclusive access to the resource
    }
}

int main() {
    pthread_t threadRE[N];
    pthread_t threadWR[M];

    sem_init(&data_access, 0, 1);
    sem_init(&readers_counter_access, 0, 1);

    for (auto &i: threadWR)
        pthread_create(&i, nullptr, writer, nullptr);
    for (auto &i: threadRE)
        pthread_create(&i, nullptr, reader, nullptr);
    // joining all of our threads, so no one gets lost
    for (auto &i: threadRE)
        pthread_join(i, nullptr);
    for (auto &i: threadWR)
        pthread_join(i, nullptr);

    sem_destroy(&data_access);
    sem_destroy(&readers_counter_access);

    return 0;
}
