#include <stdio.h>

typedef struct
{
    int pid, at, bt, ct, tat, wt, rt, start, completed;
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
        p[i].completed = 0;
    }

    while (completed < n)
    {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= current_time && !p[i].completed)
            {
                if (p[i].bt < min_bt)
                {
                    min_bt = p[i].bt;
                    idx = i;
                }
                else if (p[i].bt == min_bt && p[i].at < p[idx].at)
                {
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            p[idx].start = current_time;
            p[idx].ct = p[idx].start + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].start - p[idx].at;

            totalTAT += p[idx].tat;
            totalWT += p[idx].wt;
            totalRT += p[idx].rt;

            current_time = p[idx].ct;
            p[idx].completed = 1;
            completed++;
        }
        else
        {
            current_time++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Response Time: %.2f\n", totalRT / n);

    return 0;
}
/*
Enter number of processes: 4
Enter Arrival Time for P1: 0
Enter Burst Time for P1: 6
Enter Arrival Time for P2: 0
Enter Burst Time for P2: 8
Enter Arrival Time for P3: 0
Enter Burst Time for P3: 7
Enter Arrival Time for P4: 0
Enter Burst Time for P4: 3

PID	AT	BT	CT	TAT	WT	RT
P1	0	6	9	9	3	3
P2	0	8	24	24	16	16
P3	0	7	16	16	9	9
P4	0	3	3	3	0	0

Average Turnaround Time: 13.00
Average Waiting Time: 7.00
Average Response Time: 7.00
*/