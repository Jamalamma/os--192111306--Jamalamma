#include <stdio.h>
#include <stdlib.h>

int main() {
    int *dynamicArray;
    int size;

    // Allocate memory using malloc
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    dynamicArray = (int *)malloc(size * sizeof(int));

    if (dynamicArray == NULL) {
        printf("Memory allocation using malloc failed.\n");
        return 1; // Exit with an error code
    }

    printf("Memory allocated using malloc at address: %p\n", dynamicArray);

    // Initialize the array elements
    for (int i = 0; i < size; ++i) {
        dynamicArray[i] = i + 1;
    }

    // Display the array elements
    printf("Array elements: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", dynamicArray[i]);
    }
    printf("\n");

    // Reallocate memory using realloc
    int newSize;
    printf("Enter the new size for the array: ");
    scanf("%d", &newSize);
    dynamicArray = (int *)realloc(dynamicArray, newSize * sizeof(int));

    if (dynamicArray == NULL) {
        printf("Memory reallocation using realloc failed.\n");
        return 1; // Exit with an error code
    }

    printf("Memory reallocated using realloc at address: %p\n", dynamicArray);

    // Display the array elements after reallocation
    printf("Array elements after reallocation: ");
    for (int i = 0; i < newSize; ++i) {
        printf("%d ", dynamicArray[i]);
    }
    printf("\n");

    // Deallocate memory using free
    free(dynamicArray);
    printf("Memory freed using free.\n");

    return 0;
}
