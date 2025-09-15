#include <stdio.h>
#include <string.h>
#define MAX 100

int main()
{
    char id[5][3] = {"P1", "P2", "P3", "P4", "P5"};
    int at[5] = {0, 1, 2, 3, 4};
    int bt[5] = {8, 4, 9, 5, 2};
    int qno[5] = {1, 2, 1, 2, 1};
    int n = 5, q = 3;

    int rem[5];
    for(int i = 0; i < n; i++) rem[i] = bt[i];

    int t = 0, completed = 0;
    int q1[MAX], q2[MAX], f1 = 0, r1 = 0, f2 = 0, r2 = 0;

    int idxs[5] = {0, 1, 2, 3, 4};
    for(int i = 0; i < 5; i++)
    {
        for(int j = i+1; j < 5; j++)
        {
            if(at[idxs[j]] < at[idxs[i]])
            {
                int tmp = idxs[i];
                idxs[i] = idxs[j];
                idxs[j] = tmp;
            }
        }
    }

    int ip = 0;
    int order[200][3], oc = 0;

    while(completed < n)
    {
        while(ip < n && at[idxs[ip]] <= t)
        {
            int p = idxs[ip];
            if(qno[p] == 1) q1[r1++] = p;
            else q2[r2++] = p;
            ip++;
        }

        if(f1 < r1)
        {
            int p = q1[f1++];
            int exec = rem[p] < q ? rem[p] : q;

            order[oc][0] = p;
            order[oc][1] = t;
            order[oc][2] = t + exec;
            oc++;

            rem[p] -= exec;
            t += exec;

            while(ip < n && at[idxs[ip]] <= t)
            {
                int np = idxs[ip];
                if(qno[np] == 1) q1[r1++] = np;
                else q2[r2++] = np;
                ip++;
            }

            if(rem[p] > 0) q1[r1++] = p;
            else completed++;
        }
        else if(f2 < r2)
        {
            int p = q2[f2];

            int next_q1_arrival = 1 << 30;
            for(int j = ip; j < n; j++)
            {
                if(qno[idxs[j]] == 1)
                {
                    next_q1_arrival = at[idxs[j]];
                    break;
                }
            }

            int exec;
            if(next_q1_arrival == (1 << 30)) exec = rem[p];
            else exec = rem[p] < (next_q1_arrival - t) ? rem[p] : (next_q1_arrival - t);

            if(exec <= 0)
            {
                t = next_q1_arrival;
                continue;
            }

            order[oc][0] = p;
            order[oc][1] = t;
            order[oc][2] = t + exec;
            oc++;

            rem[p] -= exec;
            t += exec;

            while(ip < n && at[idxs[ip]] <= t)
            {
                int np = idxs[ip];
                if(qno[np] == 1) q1[r1++] = np;
                else q2[r2++] = np;
                ip++;
            }

            if(rem[p] == 0)
            {
                f2++;
                completed++;
            }
        }
        else
        {
            if(ip < n)
            {
                t = at[idxs[ip]];
                continue;
            }
            else break;
        }
    }

    int start[5], finish[5];
    for(int i = 0; i < 5; i++)
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
    printf("Multilevel Queue Scheduling\n");
    printf("Gantt: ");
    for(int i = 0; i < oc; i++)
    {
        printf("%s: %d-%d ", id[order[i][0]], order[i][1], order[i][2]);
    }
    printf("\n");

    printf("Process AT BT Q WT TAT\n");
    for(int i = 0; i < n; i++)
    {
        int tat = finish[i] - at[i];
        int wt = tat - bt[i];
        swt += wt;
        stat += tat;
        printf("%s %d %d %d %d %d\n", id[i], at[i], bt[i], qno[i], wt, tat);
    }
    printf("Avg WT = %.2f Avg TAT = %.2f\n", swt/n, stat/n);

    return 0;
}