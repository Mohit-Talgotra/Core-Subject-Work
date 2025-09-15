#include <stdio.h>
#include <string.h>

//23BKT0075 Mohit Talgotra

int main()
{
    char id[5][3] = {"P1", "P2", "P3", "P4", "P5"};
    int at[5] = {0, 1, 2, 3, 4};
    int bt[5] = {5, 3, 6, 1, 5};
    int n = 5;

    int done[5] = {0};
    int t = 0, c = 0;
    int start[5], finish[5];
    while(c < n)
    {
        int idx = -1;
        int minb = 1 << 30;
        for(int i = 0; i < n; i++)
        {
            if(!done[i] && at[i] <= t)
            {
                if(bt[i] < minb || (bt[i] == minb && at[i] < at[idx]))
                {
                    minb = bt[i];
                    idx = i;
                }
            }
        }
        if(idx == -1)
        {
            t++;
            continue;
        }
        start[idx] = t;
        t += bt[idx];
        finish[idx] = t;
        done[idx] = 1;
        c++;
    }

    int wt[5], tat[5];
    double swt = 0, stat = 0;
    printf("SJF Non-Preemptive\n");
    printf("Gantt: ");
    for(int i = 0; i < n; i++)
    {
        printf("%s: %d-%d ", id[i], start[i], finish[i]);
    }
    printf("\n");
    for(int i = 0; i < n; i++)
    {
        tat[i] = finish[i] - at[i];
        wt[i] = start[i] - at[i];
        swt += wt[i];
        stat += tat[i];
    }
    printf("Process AT BT WT TAT\n");
    for(int i = 0; i < n; i++)
    {
        printf("%s %d %d %d %d\n", id[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("Avg WT = %.2f Avg TAT = %.2f\n\n", swt/n, stat/n);

    int pr[5] = {2, 1, 3, 4, 2};
    for(int i = 0; i < n; i++) done[i] = 0;
    t = 0; c = 0;
    while(c < n)
    {
        int idx = -1;
        int minp = 1 << 30;
        for(int i = 0; i < n; i++)
        {
            if(!done[i] && at[i] <= t)
            {
                if(pr[i] < minp || (pr[i] == minp && at[i] < at[idx]))
                {
                    minp = pr[i];
                    idx = i;
                }
            }
        }
        if(idx == -1)
        {
            t++;
            continue;
        }
        start[idx] = t;
        t += bt[idx];
        finish[idx] = t;
        done[idx] = 1;
        c++;
    }
    swt = 0; stat = 0;
    printf("Priority Non-Preemptive\n");
    printf("Gantt: ");
    for(int i = 0; i < n; i++)
    {
        printf("%s: %d-%d ", id[i], start[i], finish[i]);
    }
    printf("\n");
    printf("Process AT BT PR WT TAT\n");
    for(int i = 0; i < n; i++)
    {
        tat[i] = finish[i] - at[i];
        wt[i] = start[i] - at[i];
        swt += wt[i];
        stat += tat[i];
        printf("%s %d %d %d %d %d\n", id[i], at[i], bt[i], pr[i], wt[i], tat[i]);
    }
    printf("Avg WT = %.2f Avg TAT = %.2f\n", swt/n, stat/n);

    return 0;
}
