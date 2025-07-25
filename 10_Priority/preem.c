#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int Id, AT, BT, CT, TAT, WT, priority;
} pro;

pro p[15];

int main()
{
    int n, tempBT[15], total_WT = 0, total_TAT = 0;
    float avg_WT = 0, avg_TAT = 0;

    printf("\nEnter the number of processes:\n");
    scanf("%d", &n);

    printf("\nEnter the arrival time, burst time and priority of the process:\n");
    printf("AT BT P\n");
    for (int i = 0; i < n; i++)
    {
        p[i].Id = i + 1;
        scanf("%d%d%d", &p[i].AT, &p[i].BT, &p[i].priority);
        tempBT[i] = p[i].BT;
    }

    printf("\nGantt Chart:\n");

    int minIndex, minPriority, completed = 0, curTime = 0;

    while (completed != n)
    {
        minIndex = -1;
        minPriority = 9999;

        for (int i = 0; i < n; i++)
        {
            if (p[i].AT <= curTime && p[i].BT > 0)
            {
                if (p[i].priority < minPriority ||
                    (p[i].priority == minPriority && p[i].AT < p[minIndex].AT))
                {
                    minPriority = p[i].priority;
                    minIndex = i;
                }
            }
        }

        if (minIndex != -1)
        {
            p[minIndex].BT--; // Execute for 1 unit time
            curTime++;
            printf("| P%d(1) %d", p[minIndex].Id, curTime);

            if (p[minIndex].BT == 0)
            {
                p[minIndex].CT = curTime;
                p[minIndex].TAT = p[minIndex].CT - p[minIndex].AT;
                p[minIndex].WT = p[minIndex].TAT - tempBT[minIndex];
                total_TAT += p[minIndex].TAT;
                total_WT += p[minIndex].WT;
                completed++;
            }
        }
        else
        {
            curTime++; // No process available, idle time
        }
    }

    printf("|\n");

    avg_TAT = (float)total_TAT / n;
    avg_WT = (float)total_WT / n;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tP\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].Id, p[i].AT, tempBT[i], p[i].CT, p[i].TAT, p[i].WT, p[i].priority);
    }

    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", avg_TAT, avg_WT);

    return 0;
}
/*
Enter the number of processes:
5

Enter the arrival time, burst time and priority of the process:
AT BT P
0 3 3 1 4 2 2 6 4 3 4 6 5 2 10

Gantt Chart:
| P1(1) 1| P2(1) 2| P2(1) 3| P2(1) 4| P2(1) 5| P1(1) 6| P1(1) 7| P3(1) 8| P3(1) 9| P3(1) 10| P3(1) 11| P3(1) 12| P3(1) 13| P4(1) 14| P4(1) 15| P4(1) 16| P4(1) 17| P5(1) 18| P5(1) 19|

PID	AT	BT	CT	TAT	WT	P
1	0	3	7	7	4	3
2	1	4	5	4	0	2
3	2	6	13	11	5	4
4	3	4	17	14	10	6
5	5	2	19	14	12	10

Average TAT = 10.00
Average WT = 6.20
*/