#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

// Define a structure for the message
struct message {
    long mtype; // Message type (must be > 0)
    char mtext[100]; // Message data
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Create a temporary file for ftok
    FILE *fp = fopen("msgq_temp_file", "w");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    // Generate a unique key for the message queue
    key = ftok("msgq_temp_file", 'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue (IPC_CREAT: create if it doesn't exist)
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Process 1: Send a message to the message queue
    if (fork() == 0) {
        strcpy(msg.mtext, "Hello from Process 1!");
        msg.mtype = 1; // Message type (must be > 0)

        // Send the message to the message queue
        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }

    // Process 2: Receive a message from the message queue
    else {
        // Wait for the child process to finish (Process 1)
        wait(NULL);

        // Receive the message from the message queue
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        printf("Received message in Process 2: %s\n", msg.mtext);

        // Remove the message queue
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(EXIT_FAILURE);
        }

        // Remove the temporary file
        if (remove("msgq_temp_file") == -1) {
            perror("remove");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }

    return 0;
}
