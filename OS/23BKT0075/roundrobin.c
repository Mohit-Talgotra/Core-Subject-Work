#include <stdio.h>
#include <string.h>
#define MAX 50

int main()
{
    char id[6][3] = {"P1", "P2", "P3", "P4", "P5", "P6"};
    int at[6] = {5, 4, 3, 1, 2, 6};
    int bt[6] = {5, 6, 7, 9, 2, 3};
    int n = 6, q = 3;

    int rem[6];
    for(int i = 0; i < n; i++) rem[i] = bt[i];

    int t = 0, completed = 0;
    int queue[MAX], front = 0, rear = 0;
    int inq[6] = {0};
    int order[200][3], oc = 0;

    int idxs[6] = {0, 1, 2, 3, 4, 5};
    for(int i = 0; i < 6; i++)
    {
        for(int j = i+1; j < 6; j++)
        {
            if(at[idxs[j]] < at[idxs[i]])
            {
                int tmp = idxs[i];
                idxs[i] = idxs[j];
                idxs[j] = tmp;
            }
        }
    }

    int idxptr = 0;
    while(completed < n)
    {
        while(idxptr < n && at[idxs[idxptr]] <= t)
        {
            int pid = idxs[idxptr];
            queue[rear++] = pid;
            inq[pid] = 1;
            idxptr++;
        }
        if(front == rear)
        {
            if(idxptr < n)
            {
                t = at[idxs[idxptr]];
                continue;
            }
            else break;
        }
        int pid = queue[front++];
        int exec = rem[pid] < q ? rem[pid] : q;
        order[oc][0] = pid;
        order[oc][1] = t;
        order[oc][2] = t + exec;
        oc++;
        rem[pid] -= exec;
        t += exec;
        while(idxptr < n && at[idxs[idxptr]] <= t)
        {
            int np = idxs[idxptr];
            if(!inq[np])
            {
                queue[rear++] = np;
                inq[np] = 1;
            }
            idxptr++;
        }
        if(rem[pid] > 0) queue[rear++] = pid;
        else completed++;
    }

    int finish[6], start[6];
    for(int i = 0; i < 6; i++)
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
    printf("Round Robin (q = %d)\n", q);
    printf("Gantt: ");
    for(int i = 0; i < oc; i++)
    {
        printf("%s: %d-%d ", id[order[i][0]], order[i][1], order[i][2]);
    }
    printf("\n");

    printf("Process AT BT WT TAT\n");
    for(int i = 0; i < n; i++)
    {
        int tat = finish[i] - at[i];
        int wt = tat - bt[i];
        swt += wt;
        stat += tat;
        printf("%s %d %d %d %d\n", id[i], at[i], bt[i], wt, tat);
    }
    printf("Avg WT = %.2f Avg TAT = %.2f\n", swt/n, stat/n);

    return 0;
}