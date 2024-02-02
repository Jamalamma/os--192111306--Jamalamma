#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";
    char buffer[100];

    // Creating a file and writing to it
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file!\n");
        return 1;
    }

    printf("Enter data to write to the file:\n");
    fgets(buffer, sizeof(buffer), stdin);
    fprintf(file, "%s", buffer);

    fclose(file);

    // Reading from the file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }

    printf("\nContent of the file:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);

    return 0;
}
