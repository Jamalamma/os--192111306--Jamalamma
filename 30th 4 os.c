#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    printf("Hello from the new thread!\n");
    pthread_exit((void *)42);
}

int main() {
    pthread_t thread;
    void *returnValue;

    if (pthread_create(&thread, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread.\n");
        return 1;
    }

    if (pthread_join(thread, &returnValue) != 0) {
        fprintf(stderr, "Error joining thread.\n");
        return 1;
    }

    printf("Main thread: New thread has terminated with value %ld.\n", (long)returnValue);

    pthread_exit(NULL);
}
