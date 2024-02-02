#include<stdio.h>
#include<stdlib.h>

// Function to perform C-SCAN disk scheduling
void cscan(int requests[], int n, int start, int maxCylinder) {
    int distance = 0;
    int currentPosition = start;

    // Sort the requests in ascending order
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                // Swap requests
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Find the position of start in the sorted requests
    int pos;
    for (pos = 0; pos < n; pos++) {
        if (requests[pos] >= start) {
            break;
        }
    }

    // Move towards the end
    for (i = pos; i < n; i++) {
        distance += abs(currentPosition - requests[i]);
        currentPosition = requests[i];
    }

    // Move to the beginning
    distance += abs(currentPosition - maxCylinder);
    currentPosition = 0;

    // Move towards the end again
    for (i = 0; i < pos; i++) {
        distance += abs(currentPosition - requests[i]);
        currentPosition = requests[i];
    }

    printf("Total distance: %d\n", distance);
}

int main() {
    int n, start, maxCylinder;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int *requests = (int *)malloc(n * sizeof(int));

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &start);

    printf("Enter the maximum cylinder size: ");
    scanf("%d", &maxCylinder);

    cscan(requests, n, start, maxCylinder);

    free(requests);

    return 0;
}
