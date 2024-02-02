#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>

#define FILENAME "shm_example_file"
#define SHM_SIZE 1024

int main() {
    // Create a file for ftok
    int fd = open(FILENAME, O_CREAT | O_RDWR, 0666);
    close(fd);

    // Create a key for shared memory
    key_t key = ftok(FILENAME, 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a shared memory segment
    int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment to the process's address space
    char *shm_ptr = (char*) shmat(shm_id, NULL, 0);
    if (shm_ptr == (char*) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Write data to the shared memory
    printf("Enter data to be written to shared memory: ");
    fgets(shm_ptr, SHM_SIZE, stdin);

    // Detach the shared memory segment
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Fork a new process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process

        // Attach the shared memory segment to the child process's address space
        char *child_shm_ptr = (char*) shmat(shm_id, NULL, 0);
        if (child_shm_ptr == (char*) -1) {
            perror("shmat in child process");
            exit(EXIT_FAILURE);
        }

        // Read and print the data from shared memory
        printf("Child process reads from shared memory: %s\n", child_shm_ptr);

        // Detach the shared memory segment from the child process
        if (shmdt(child_shm_ptr) == -1) {
            perror("shmdt in child process");
            exit(EXIT_FAILURE);
        }

    } else {
        // Parent process

        // Wait for the child process to finish
        wait(NULL);

        // Remove the shared memory segment
        if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(EXIT_FAILURE);
        }

        // Remove the file used for ftok
        remove(FILENAME);
    }

    return 0;
}
