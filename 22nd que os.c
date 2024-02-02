#include <stdio.h>

#define MAX_BLOCKS 50

struct Block {
    int size;
    int allocated;
};

void initializeBlocks(struct Block blocks[], int numBlocks) {
    for (int i = 0; i < numBlocks; ++i) {
        blocks[i].size = 0;
        blocks[i].allocated = 0;
    }
}

void printBlocks(struct Block blocks[], int numBlocks) {
    printf("\nMemory Blocks:\n");
    for (int i = 0; i < numBlocks; ++i) {
        printf("Block %d: Size = %d, Allocated = %d\n", i + 1, blocks[i].size, blocks[i].allocated);
    }
    printf("\n");
}

int bestFit(struct Block blocks[], int numBlocks, int requestedSize) {
    int bestFitIndex = -1;

    for (int i = 0; i < numBlocks; ++i) {
        if (!blocks[i].allocated && blocks[i].size >= requestedSize) {
            if (bestFitIndex == -1 || blocks[i].size < blocks[bestFitIndex].size) {
                bestFitIndex = i;
            }
        }
    }

    return bestFitIndex;
}

void allocateMemory(struct Block blocks[], int numBlocks, int requestedSize, int processId) {
    int index = bestFit(blocks, numBlocks, requestedSize);

    if (index != -1) {
        blocks[index].allocated = 1;
        printf("Memory allocated for Process %d in Block %d\n", processId, index + 1);
    } else {
        printf("Unable to allocate memory for Process %d\n", processId);
    }
}

int main() {
    struct Block blocks[MAX_BLOCKS];
    int numBlocks, numProcesses;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);

    printf("Enter the sizes of memory blocks:\n");
    for (int i = 0; i < numBlocks; ++i) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i].size);
        blocks[i].allocated = 0;
    }

    printBlocks(blocks, numBlocks);

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    for (int i = 1; i <= numProcesses; ++i) {
        int requestedSize;
        printf("\nEnter memory size requested by Process %d: ", i);
        scanf("%d", &requestedSize);

        allocateMemory(blocks, numBlocks, requestedSize, i);

        printBlocks(blocks, numBlocks);
    }

    return 0;
}
