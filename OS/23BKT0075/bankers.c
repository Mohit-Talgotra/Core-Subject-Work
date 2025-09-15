#include <stdio.h>

//23BKT0075 Mohit Talgotra

int main()
{
    int P, R;
    printf("Number of processes: ");
    scanf("%d", &P);
    printf("Number of resource types: ");
    scanf("%d", &R);
    int alloc[P][R], max[P][R], avail[R], need[P][R], finish[P], work[R], safeSeq[P], count = 0;
    printf("Allocation:\n");
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    
    printf("Max:\n");
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("Available:\n");
    for (int j = 0; j < R; j++)
    {
        scanf("%d", &avail[j]);
    }
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    for (int i = 0; i < P; i++)
    {
        finish[i] = 0;
    }
    for (int j = 0; j < R; j++)
    {
        work[j] = avail[j];
    }
    for (int k = 0; k < P; k++)
    {
        for (int i = 0; i < P; i++)
        {
            if (!finish[i])
            {
                int can = 1;
                for (int j = 0; j < R; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        can = 0;
                        break;
                    }
                }
                if (can)
                {
                    for (int j = 0; j < R; j++)
                    {
                        work[j] += alloc[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                }
            }
        }
    }
    if (count == P)
    {
        printf("System is in a safe state\nSafe sequence: ");
        for (int i = 0; i < P; i++)
        {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    }
    else
    {
        printf("System is not in a safe state\n");
    }
    
    int req[R], p;
    printf("Which process is requesting? ");
    scanf("%d", &p);
    
    printf("Resource request:\n");
    for (int j = 0; j < R; j++)
    {
        scanf("%d", &req[j]);
    }
    int ok = 1;
    for (int j = 0; j < R; j++)
    {
        if (req[j] > need[p][j])
        {
            ok = 0;
        }
    }
    for (int j = 0; j < R; j++)
    {
        if (req[j] > avail[j])
        {
            ok = 0;
        }
    }
    if (ok)
    {
        for (int j = 0; j < R; j++)
        {
            avail[j] -= req[j];
            alloc[p][j] += req[j];
            need[p][j] -= req[j];
        }
        for (int j = 0; j < R; j++)
        {
            work[j] = avail[j];
        }
        for (int i = 0; i < P; i++)
        {
            finish[i] = 0;
        }
        count = 0;
        for (int k = 0; k < P; k++)
        {
            for (int i = 0; i < P; i++)
            {
                if (!finish[i])
                {
                    int can = 1;
                    for (int j = 0; j < R; j++)
                    {
                        if (need[i][j] > work[j])
                        {
                            can = 0;
                            break;
                        }
                    }
                    if (can)
                    {
                        for (int j = 0; j < R; j++)
                        {
                            work[j] += alloc[i][j];
                        }
                        safeSeq[count++] = i;
                        finish[i] = 1;
                    }
                }
            }
        }
        if (count == P)
        {
            printf("Request can be granted\nNew safe sequence: ");
            for (int i = 0; i < P; i++)
            {
                printf("P%d ", safeSeq[i]);
            }
            printf("\n");
        }
        else
        {
            printf("Request cannot be granted\n");
        }
    }
    else
    {
        printf("Request is invalid\n");
    }
    return 0;
}