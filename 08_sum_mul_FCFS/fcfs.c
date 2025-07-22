#include <stdio.h>

typedef struct node
{
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
} Process;

void fcfs(Process[], int);

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Accept process details from the user
    for (int i = 0; i < n; i++)
    {
        processes[i].processId = i + 1;
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("\n");
    }

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Perform FCFS scheduling
    fcfs(processes, n);
    return 0;
}

void fcfs(Process processes[], int n)
{
    int elapsedTime = 0;
    float totalWaitingTime = 0;
    float totalTurnAroundTime = 0;
    float totalResponseTime = 0;

    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrivalTime > elapsedTime)
        {
            elapsedTime = processes[i].arrivalTime; // CPU idle time
        }

        int temp = elapsedTime;
        processes[i].responseTime = elapsedTime - processes[i].arrivalTime;
        elapsedTime += processes[i].burstTime;
        processes[i].completionTime = elapsedTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        printf("| P%d (%d - %d) ", processes[i].processId, temp, elapsedTime);

        totalTurnAroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;
        totalResponseTime += processes[i].responseTime;
    }
    printf("|\n");

    // Display Observation Table
    printf("\nObservation Table:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].processId,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime,
               processes[i].responseTime);
    }

    // Print average metrics
    float avgTurnAroundTime = totalTurnAroundTime / n;
    float avgWaitingTime = totalWaitingTime / n;
    float avgResponseTime = totalResponseTime / n;

    printf("\nAverage Turnaround Time: %.2f", avgTurnAroundTime);
    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
    printf("\nAverage Response Time: %.2f\n", avgResponseTime);
}
/*
Enter the number of processes: 5
Enter Arrival Time for Process 1: 4
Enter Burst Time for Process 1: 5

Enter Arrival Time for Process 2: 6
Enter Burst Time for Process 2: 4

Enter Arrival Time for Process 3: 0
Enter Burst Time for Process 3: 3

Enter Arrival Time for Process 4: 6
Enter Burst Time for Process 4: 2

Enter Arrival Time for Process 5: 5
Enter Burst Time for Process 5: 4


Gantt Chart:
| P3 (0 - 3) | P1 (4 - 9) | P5 (9 - 13) | P2 (13 - 17) | P4 (17 - 19) |

Observation Table:
PID	AT	BT	CT	TAT	WT	RT
3	0	3	3	3	0	0
1	4	5	9	5	0	0
5	5	4	13	8	4	4
2	6	4	17	11	7	7
4	6	2	19	13	11	11

Average Turnaround Time: 8.00
Average Waiting Time: 4.40
Average Response Time: 4.40

*/