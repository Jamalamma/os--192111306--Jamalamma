#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // File I/O
    int file_descriptor;
    ssize_t bytesRead, bytesWritten;

    // Open or create a file
    file_descriptor = open("example_file.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (file_descriptor == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write content to the file
    const char *content = "Hello, this is a demonstration of I/O system calls in UNIX!";
    bytesWritten = write(file_descriptor, content, strlen(content));
    if (bytesWritten == -1) {
        perror("Error writing to file");
        close(file_descriptor);
        exit(EXIT_FAILURE);
    }

    // Move the file cursor to the beginning
    lseek(file_descriptor, 0, SEEK_SET);

    // Read and display the content of the file
    char buffer[1024];
    bytesRead = read(file_descriptor, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("Error reading from file");
        close(file_descriptor);
        exit(EXIT_FAILURE);
    }

    printf("File Content:\n%s\n", buffer);

    // Close the file
    close(file_descriptor);

    // Directory listing
    DIR *dir;
    struct dirent *entry;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // Read and display the contents of the directory
    printf("\nDirectory Contents:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}
