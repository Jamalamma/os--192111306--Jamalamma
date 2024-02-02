#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define ITERATIONS 100000

// Shared data
int counter = 0;
pthread_mutex_t mutex;

// Thread function to increment the counter
void *incrementCounter(void *threadID) {
    long tid = (long)threadID;

    for (int i = 0; i < ITERATIONS; ++i) {
        // Acquire the mutex lock
        pthread_mutex_lock(&mutex);

        // Critical section: Increment the shared counter
        counter++;

        // Release the mutex lock
        pthread_mutex_unlock(&mutex);
    }

    printf("Thread %ld completed. Counter: %d\n", tid, counter);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (t = 0; t < NUM_THREADS; ++t) {
        rc = pthread_create(&threads[t], NULL, incrementCounter, (void *)t);
        if (rc) {
            printf("Error: Unable to create thread %ld. Code: %d\n", t, rc);
            exit(-1);
        }
    }

    // Join threads
    for (t = 0; t < NUM_THREADS; ++t) {
        pthread_join(threads[t], NULL);
    }

    // Display the final value of the counter
    printf("Final counter value: %d\n", counter);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    pthread_exit(NULL);
}
