#include <stdio.h>
#include <stdlib.h>

void scan(int arr[], int head, int size) {
    int distance = 0;
    int cur_track;
    int left, right;

    // Separate the requests into two queues: left and right
    int left_queue[size], right_queue[size];
    int left_size = 0, right_size = 0;

    // Identify the requests on the left and right sides of the head
    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left_queue[left_size++] = arr[i];
        else
            right_queue[right_size++] = arr[i];
    }

    // Sort the left and right queues
    for (int i = 0; i < left_size - 1; i++) {
        for (int j = 0; j < left_size - i - 1; j++) {
            if (left_queue[j] < left_queue[j + 1]) {
                int temp = left_queue[j];
                left_queue[j] = left_queue[j + 1];
                left_queue[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < right_size - 1; i++) {
        for (int j = 0; j < right_size - i - 1; j++) {
            if (right_queue[j] > right_queue[j + 1]) {
                int temp = right_queue[j];
                right_queue[j] = right_queue[j + 1];
                right_queue[j + 1] = temp;
            }
        }
    }

    left = right = 0;

    // Scan from left to right
    for (int i = 0; i < right_size; i++) {
        cur_track = right_queue[i];
        printf("Move from %d to %d\n", head, cur_track);
        distance += abs(head - cur_track);
        head = cur_track;
    }

    // Scan from right to left
    for (int i = 0; i < left_size; i++) {
        cur_track = left_queue[i];
        printf("Move from %d to %d\n", head, cur_track);
        distance += abs(head - cur_track);
        head = cur_track;
    }

    printf("Total distance: %d\n", distance);
}

int main() {
    int size, head;

    printf("Enter the size of the disk queue: ");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the disk queue elements:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    scan(arr, head, size);

    return 0;
}
