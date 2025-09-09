#include <stdio.h>
#include <limits.h>

typedef struct
{
    int pid, at, bt, rt, ct, tat, wt, start;
    int is_completed;
} Process;

int main()
{
    int n, completed = 0, current_time = 0;
    float totalTAT = 0, totalWT = 0, totalRT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter Arrival Time for P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].pid = i + 1;
        p[i].rt = p[i].bt;
        p[i].start = -1;
        p[i].is_completed = 0;
    }

    while (completed < n)
    {
        int idx = -1, min_rt = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= current_time && p[i].rt > 0 && p[i].rt < min_rt)
            {
                min_rt = p[i].rt;
                idx = i;
            }
        }

        if (idx != -1)
        {
            if (p[idx].start == -1)
                p[idx].start = current_time;

            p[idx].rt--;
            current_time++;

            if (p[idx].rt == 0)
            {
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].is_completed = 1;

                // response time = start - arrival
                totalRT += p[idx].start - p[idx].at;
                totalTAT += p[idx].tat;
                totalWT += p[idx].wt;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        int rt = p[i].start - p[i].at;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, rt);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Response Time: %.2f\n", totalRT / n);

    return 0;
}
/*
Enter number of processes: 4
Enter Arrival Time for P1: 0
Enter Burst Time for P1: 8
Enter Arrival Time for P2: 1
Enter Burst Time for P2: 4
Enter Arrival Time for P3: 2
Enter Burst Time for P3: 9
Enter Arrival Time for P4: 3
Enter Burst Time for P4: 5

PID	AT	BT	CT	TAT	WT	RT
P1	0	8	17	17	9	0
P2	1	4	5	4	0	0
P3	2	9	26	24	15	15
P4	3	5	10	7	2	2

Average Turnaround Time: 13.00
Average Waiting Time: 6.50
Average Response Time: 4.25
*/