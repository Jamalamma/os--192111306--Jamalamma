#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void listFiles(const char *path) {
    DIR *dir;
    struct dirent *entry;

    // Open the specified directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Read and print the contents of the directory
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);
}

int main(int argc, char *argv[]) {
    // Check if a directory path is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // List the files in the specified directory
    listFiles(argv[1]);

    return 0;
}
