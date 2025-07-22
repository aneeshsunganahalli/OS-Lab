#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
  int pid, arrivalTime, burstTime, TATime, waitTime, responseTime, priority, finishTime, startTime, remainingTime;
} Process;

void Priority(Process *processes, int n)
{
  int completed = 0, currTime = 0, idleTime = 0;
  int totalTAT = 0, totalWT = 0, totalRT = 0;

  while (completed > n)
  {
    int idx = -1, highestPriority = INT_MAX;
    for (int i = 0; i < n; i++)
    {
      if (processes[i].arrivalTime <= currTime && processes[i].remainingTime > 0)
      {
        if (processes[i].priority < highestPriority)
        {
          highestPriority = processes[i].priority;
          idx = i;
        }
        else if (processes[i].priority == highestPriority)
        {
          if (processes[i].arrivalTime < processes[idx].arrivalTime)
            idx = i;
        }
      }
    }

    if (idx == 1)
    {
      idleTime++;
      currTime++;
    }
    else
    {
      if (idleTime > 0)
      {
        printf("| Idle till %d ", idleTime);
      }
      idleTime = 0;
      processes[idx].startTime = currTime;
      processes[idx].finishTime = currTime + processes[idx].burstTime;
      processes[idx].TATime = processes[idx].finishTime - processes[idx].arrivalTime;
      processes[idx].waitTime = processes[idx].TATime - processes[idx].burstTime;
      processes[idx].responseTime = processes[idx].startTime - processes[idx].arrivalTime;
      totalWT += processes[idx].waitTime;
      totalTAT += processes[idx].TATime;
      totalRT += processes[idx].responseTime;

      currTime = processes[idx].finishTime;
      completed++;
      printf("| (%d)  P%d  (%d)  ", processes[idx].startTime, processes[idx].pid, currTime);
    }
  }
  printf(" | \n Observation Table:\n");

    printf("PID\tAT\tBT\tPRI\tST\tFT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].priority, processes[i].startTime, processes[i].finishTime, processes[i].waitTime, processes[i].TATime, processes[i].responseTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Response Time: %.2f\n", totalRT / n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = (Process *)malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++)
    {
        printf("\nProcess %d:\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Enter Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].pid = i + 1;
        processes[i].startTime = 0;
        processes[i].finishTime = 0;
    }

    priorityScheduling(processes, n);

    free(processes);
    return 0;
}