#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, wrt;
int read_count = 0;

void *reader(void *arg) {
    int reader_id = *(int *)arg;

    while (1) {
        // Entry Section
        sem_wait(&mutex);
        read_count++;

        if (read_count == 1) {
            sem_wait(&wrt); // If this is the first reader, block writers
        }

        sem_post(&mutex);

        // Critical Section (Reading)
        printf("Reader %d is reading...\n", reader_id);
        // Reading...

        // Exit Section
        sem_wait(&mutex);
        read_count--;

        if (read_count == 0) {
            sem_post(&wrt); // If this is the last reader, allow writers
        }

        sem_post(&mutex);

        // Non-critical Section
        // (Reading is complete)
        sleep(rand() % 3); // Simulate some processing time
    }

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;

    while (1) {
        // Entry Section
        sem_wait(&wrt);

        // Critical Section (Writing)
        printf("Writer %d is writing...\n", writer_id);
        // Writing...

        // Exit Section
        sem_post(&wrt);

        // Non-critical Section
        // (Writing is complete)
        sleep(rand() % 3); // Simulate some processing time
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
