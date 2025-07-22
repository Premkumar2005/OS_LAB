#include <stdio.h>

typedef struct process
{
    int Id, AT, BT, CT, TAT, WT, isCompl, priority;
} pro;

pro p[15];

int main()
{
    int n, total_WT = 0, total_TAT = 0, idleTime = 0;
    float avg_WT = 0, avg_TAT = 0;

    printf("\nEnter the number of processes:\n");
    scanf("%d", &n);

    printf("\nEnter the Arrival Time, Burst Time and Priority of each process:\n");
    printf("AT BT Priority\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &p[i].AT, &p[i].BT, &p[i].priority);
        p[i].Id = i + 1;
        p[i].isCompl = 0;
    }

    int completed = 0, curTime = 0;

    printf("\nGantt Chart:\n\n");

    while (completed != n)
    {
        int minIndex = -1;
        int minPriority = 9999;

        for (int i = 0; i < n; i++)
        {
            if (p[i].AT <= curTime && p[i].isCompl == 0)
            {
                if (p[i].priority < minPriority || (p[i].priority == minPriority && p[i].AT < p[minIndex].AT))
                {
                    minPriority = p[i].priority;
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1)
        {
            printf("| Idle till %d ", curTime + 1);
            curTime++;
            idleTime++;
        }
        else
        {
            if (idleTime > 0)
            {
                idleTime = 0;
            }

            curTime += p[minIndex].BT;
            p[minIndex].CT = curTime;
            p[minIndex].TAT = p[minIndex].CT - p[minIndex].AT;
            p[minIndex].WT = p[minIndex].TAT - p[minIndex].BT;
            total_TAT += p[minIndex].TAT;
            total_WT += p[minIndex].WT;
            p[minIndex].isCompl = 1;
            completed++;

            printf("| P%d (%d) %d ", p[minIndex].Id, p[minIndex].BT, p[minIndex].CT);
        }
    }

    printf("|\n");

    avg_TAT = (float)total_TAT / n;
    avg_WT = (float)total_WT / n;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tPriority\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].Id, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT, p[i].priority);
    }

    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", avg_TAT, avg_WT);

    return 0;
}
/*
Enter the number of processes:
4

Enter the Arrival Time, Burst Time and Priority of each process:
AT BT Priority
0 4 2
1 3 1
2 1 3
3 2 2
Gantt Chart:

| P1 (4) 4 | P2 (3) 7 | P4 (2) 9 | P3 (1) 10 |
PID	AT	BT	CT	TAT	WT	Priority
1	0	4	4	4	0	2
2	1	3	7	6	3	1
3	2	1	10	8	7	3
4	3	2	9	6	4	2

Average TAT = 6.00
Average WT = 3.50
*/