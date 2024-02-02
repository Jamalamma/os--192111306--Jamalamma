#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int file_descriptor;
    ssize_t bytesRead, bytesWritten;

    // Create a new file or open an existing file
    file_descriptor = open("example_file.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (file_descriptor == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write content to the file
    const char *content = "Hello, this is a demonstration of UNIX system calls for file management!";
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

    return 0;
}
