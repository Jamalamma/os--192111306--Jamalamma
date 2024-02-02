#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void grep(FILE *file, const char *pattern) {
    char line[MAX_LINE_LENGTH];

    // Read lines from the file or standard input
    while (fgets(line, sizeof(line), file) != NULL) {
        // Check if the line contains the specified pattern
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if both the pattern and file name are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pattern> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *pattern = argv[1];
    const char *filename = argv[2];

    FILE *file;
    
    if (strcmp(filename, "-") == 0) {
        // Use stdin if the filename is "-"
        file = stdin;
    } else {
        // Open the specified file
        file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
    }

    // Perform grep operation
    grep(file, pattern);

    // Close the file if it's not stdin
    if (file != stdin) {
        fclose(file);
    }

    return 0;
}
