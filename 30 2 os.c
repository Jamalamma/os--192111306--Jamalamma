#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    printf("Hello from the new thread!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;

    if (pthread_create(&thread, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread.\n");
        return 1;
    }

    printf("Hello from the main thread!\n");

    if (pthread_join(thread, NULL) != 0) {
        fprintf(stderr, "Error joining thread.\n");
        return 1;
    }

    printf("Main thread: New thread has terminated.\n");

    pthread_exit(NULL);
}
