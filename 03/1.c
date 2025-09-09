#include <stdio.h>

typedef struct process
{
    int Id, AT, BT, CT, TAT, WT, RT;
} pro;

int main()
{
    int n, tq, curTime = 0, completed = 0;
    float total_TAT = 0, total_WT = 0;
    pro p[20];
    int queue[100], front = 0, rear = 0;
    int visited[20] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time (AT BT):\n");
    for (int i = 0; i < n; i++)
    {
        p[i].Id = i + 1;
        scanf("%d%d", &p[i].AT, &p[i].BT);
        p[i].RT = p[i].BT;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Sort processes by Arrival Time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].AT > p[j + 1].AT)
            {
                pro temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    queue[rear++] = 0;
    visited[0] = 1;

    printf("\nGantt Chart:\n");

    while (completed < n)
    {
        int idx = queue[front++];
        if (p[idx].RT > tq)
        {
            printf("| P%d %d ", p[idx].Id, curTime);
            curTime += tq;
            p[idx].RT -= tq;
        }
        else
        {
            printf("| P%d %d ", p[idx].Id, curTime);
            curTime += p[idx].RT;
            p[idx].RT = 0;
            p[idx].CT = curTime;
            p[idx].TAT = p[idx].CT - p[idx].AT;
            p[idx].WT = p[idx].TAT - p[idx].BT;
            total_TAT += p[idx].TAT;
            total_WT += p[idx].WT;
            completed++;
        }

        // Enqueue processes that have arrived and not yet visited
        for (int i = 0; i < n; i++)
        {
            if (i != idx && !visited[i] && p[i].AT <= curTime)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // Re-enqueue current process if it's not completed
        if (p[idx].RT > 0)
        {
            queue[rear++] = idx;
        }

        // If queue becomes empty, find next arriving process
        if (front == rear)
        {
            for (int i = 0; i < n; i++)
            {
                if (p[i].RT > 0)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }

    printf("| %d\n", curTime);

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].Id, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", total_TAT / n, total_WT / n);

    return 0;
}
