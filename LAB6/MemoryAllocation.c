#include <stdio.h>

void firstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[processes];
    int used[blocks];

    for (int i = 0; i < processes; i++)
        allocation[i] = -1;

    for (int i = 0; i < blocks; i++)
        used[i] = 0;

    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < blocks; j++)
        {
            if (!used[j] && blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                used[j] = 1;
                break;
            }
        }
    }

    printf("\n--- First Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (int i = 0; i < processes; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[processes];
    int used[blocks];

    for (int i = 0; i < processes; i++)
        allocation[i] = -1;

    for (int i = 0; i < blocks; i++)
        used[i] = 0;

    for (int i = 0; i < processes; i++)
    {
        int bestIdx = -1;

        for (int j = 0; j < blocks; j++)
        {
            if (!used[j] && blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            used[bestIdx] = 1;
        }
    }

    printf("\n--- Best Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (int i = 0; i < processes; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[processes];
    int used[blocks];

    for (int i = 0; i < processes; i++)
        allocation[i] = -1;

    for (int i = 0; i < blocks; i++)
        used[i] = 0;

    for (int i = 0; i < processes; i++)
    {
        int worstIdx = -1;

        for (int j = 0; j < blocks; j++)
        {
            if (!used[j] && blockSize[j] >= processSize[i])
            {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            used[worstIdx] = 1;
        }
    }

    printf("\n--- Worst Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (int i = 0; i < processes; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main()
{
    int blocks, processes;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);

    int blockSize[blocks];

    printf("Enter sizes of memory blocks:\n");

    for (int i = 0; i < blocks; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &processes);

    int processSize[processes];

    printf("Enter sizes of processes:\n");

    for (int i = 0; i < processes; i++)
        scanf("%d", &processSize[i]);

    firstFit(blockSize, blocks, processSize, processes);
    bestFit(blockSize, blocks, processSize, processes);
    worstFit(blockSize, blocks, processSize, processes);

    return 0;
}