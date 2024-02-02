#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    printf("Hello from the new thread!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, threadFunction, NULL) != 0 ||
        pthread_create(&thread2, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating threads.\n");
        return 1;
    }

    if (pthread_equal(thread1, thread2)) {
        printf("Threads are equal.\n");
    } else {
        printf("Threads are not equal.\n");
    }

    pthread_exit(NULL);
}
