#include <stdio.h>

// Structure to represent a memory block
struct MemoryBlock {
    int id;           // Block ID
    int size;         // Block size
    int allocated;    // 1 if allocated, 0 if free
};

// Function to allocate memory using First Fit algorithm
void firstFit(struct MemoryBlock memory[], int numBlocks, int processId, int processSize) {
    for (int i = 0; i < numBlocks; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            // Allocate memory
            memory[i].id = processId;
            memory[i].allocated = 1;
            printf("Process %d allocated to Memory Block %d\n", processId, memory[i].id);
            return;
        }
    }

    // If no suitable block is found
    printf("Process %d cannot be allocated. No suitable block found.\n", processId);
}

// Function to display the current state of memory
void displayMemory(struct MemoryBlock memory[], int numBlocks) {
    printf("\nMemory Status:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: Size %d, %s\n", memory[i].id, memory[i].size,
               memory[i].allocated ? "Allocated" : "Free");
    }
    printf("\n");
}

int main() {
    // Number of memory blocks
    int numBlocks;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);

    // Initialize memory blocks
    struct MemoryBlock memory[numBlocks];
    for (int i = 0; i < numBlocks; i++) {
        memory[i].id = i + 1;
        memory[i].allocated = 0; // Initially all blocks are free
        printf("Enter size of Memory Block %d: ", memory[i].id);
        scanf("%d", &memory[i].size);
    }

    // Number of processes
    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    // Allocate memory for each process
    for (int i = 0; i < numProcesses; i++) {
        int processSize;
        printf("Enter size of Process %d: ", i + 1);
        scanf("%d", &processSize);
        firstFit(memory, numBlocks, i + 1, processSize);
        displayMemory(memory, numBlocks);
    }

    return 0;
}
