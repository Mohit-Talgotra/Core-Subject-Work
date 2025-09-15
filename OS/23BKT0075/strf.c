#include <stdio.h>
#include <string.h>
#define MAXE 1000

int main()
{
    char id[4][3] = {"P1", "P2", "P3", "P4"};
    int at[4] = {0, 1, 2, 3};
    int c1[4] = {6, 3, 4, 5};
    int io[4] = {4, 5, 3, 4};
    int c2[4] = {5, 4, 6, 2};
    int n = 4;

    int phase[4], rem[4];
    for(int i = 0; i < n; i++)
    {
        phase[i] = 1;
        rem[i] = c1[i];
    }

    int t = 0, completed = 0;
    int order[MAXE][3], oc = 0;
    int io_list[MAXE][2], io_ct = 0;

    while(completed < n)
    {
        for(int i = 0; i < n; i++)
            if(phase[i] == 1 && at[i] == t);

        for(int i = 0; i < io_ct; i++)
        {
            if(io_list[i][0] == t)
            {
                int pid = io_list[i][1];
                phase[pid] = 2;
                rem[pid] = c2[pid];
                io_list[i][0] = -1;
            }
        }

        int readyindex = -1, minrem = 1 << 30;
        for(int i = 0; i < n; i++)
        {
            if((phase[i] == 1 || phase[i] == 2) && rem[i] > 0 && at[i] <= t)
            {
                if(rem[i] < minrem || (rem[i] == minrem && at[i] < at[readyindex]))
                {
                    minrem = rem[i];
                    readyindex = i;
                }
            }
        }

        if(readyindex == -1)
        {
            int next = 1 << 30;
            for(int i = 0; i < n; i++)
                if(phase[i] == 1 && at[i] > t && at[i] < next)
                    next = at[i];
            for(int i = 0; i < io_ct; i++)
                if(io_list[i][0] > t && io_list[i][0] < next)
                    next = io_list[i][0];

            if(next == (1 << 30)) break;
            t = next;
            continue;
        }

        int pid = readyindex;
        order[oc][0] = pid;
        order[oc][1] = t;
        order[oc][2] = t + 1;
        oc++;

        rem[pid]--;
        t++;

        if(rem[pid] == 0)
        {
            if(phase[pid] == 1)
            {
                phase[pid] = 0; // I/O
                io_list[io_ct][0] = t + io[pid];
                io_list[io_ct][1] = pid;
                io_ct++;
            }
            else
            {
                phase[pid] = 3;
                completed++;
            }
        }
    }

    int start[4], finish[4];
    for(int i = 0; i < 4; i++)
    {
        start[i] = -1;
        finish[i] = 0;
    }
    for(int i = 0; i < oc; i++)
    {
        int p = order[i][0], s = order[i][1], f = order[i][2];
        if(start[p] == -1) start[p] = s;
        finish[p] = f;
    }

    double swt = 0, stat = 0;
    printf("Gantt segments:\n");
    for(int i = 0; i < oc; i++)
        printf("%s:%d-%d ", id[order[i][0]], order[i][1], order[i][2]);

    printf("\nProcess AT BT1 IO BT2 WT TAT\n");
    for(int i = 0; i < n; i++)
    {
        int tat = finish[i] - at[i];
        int wt = tat - (c1[i] + c2[i]);
        swt += wt;
        stat += tat;
        printf("%s %d %d %d %d %d %d\n", id[i], at[i], c1[i], io[i], c2[i], wt, tat);
    }
    printf("Avg WT=%.2f Avg TAT=%.2f\n", swt / n, stat / n);

    return 0;
}
