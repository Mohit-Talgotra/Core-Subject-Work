#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 50
#define MAX_PROCESSES 50

void display_blocks(int blockOriginal[], int m, int alloc[][MAX_PROCESSES], int alloc_count[])
{
    int i, j;
    for(i=0;i<m;i++)
    {
        printf("B%-2d (%-4d) ", i+1, blockOriginal[i]);
        if(alloc_count[i]==0)
        {
            printf("|      |");
        }
        else
        {
            for(j=0;j<alloc_count[i];j++)
            {
                printf("|P%-2d|", alloc[i][j]+1);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void first_fit(int blockSize[], int blockOriginal[], int m, int processSize[], int n)
{
    int alloc[MAX_BLOCKS][MAX_PROCESSES] = {0};
    int alloc_count[MAX_BLOCKS] = {0};
    int i, j;

    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                alloc[j][alloc_count[j]] = i;
                alloc_count[j]++;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    display_blocks(blockOriginal, m, alloc, alloc_count);
}

void best_fit(int blockSize[], int blockOriginal[], int m, int processSize[], int n)
{
    int alloc[MAX_BLOCKS][MAX_PROCESSES] = {0};
    int alloc_count[MAX_BLOCKS] = {0};
    int i, j;

    for(i=0;i<n;i++)
    {
        int best=-1;
        for(j=0;j<m;j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(best==-1 || blockSize[j]<blockSize[best])
                {
                    best=j;
                }
            }
        }
        if(best!=-1)
        {
            alloc[best][alloc_count[best]] = i;
            alloc_count[best]++;
            blockSize[best]-=processSize[i];
        }
    }

    display_blocks(blockOriginal, m, alloc, alloc_count);
}

int main()
{
    int m, n, i;

    int blockSizeManual1[MAX_BLOCKS] = {100, 500, 200, 300, 600};
    int blockOriginal1[MAX_BLOCKS];
    for(i=0;i<5;i++)
        blockOriginal1[i] = blockSizeManual1[i];
    int processSizeManual1[MAX_PROCESSES] = {212, 417, 112, 426};
    m = 5;
    n = 4;

    printf("Manual Input:\n\nFirst Fit Result:\n");
    first_fit(blockSizeManual1, blockOriginal1, m, processSizeManual1, n);

    int blockSizeManual2[MAX_BLOCKS] = {100, 500, 200, 300, 600};
    int blockOriginal2[MAX_BLOCKS];
    for(i=0;i<5;i++)
        blockOriginal2[i] = blockSizeManual2[i];

    printf("Best Fit Result:\n");
    best_fit(blockSizeManual2, blockOriginal2, m, processSizeManual1, n);

    return 0;
}
