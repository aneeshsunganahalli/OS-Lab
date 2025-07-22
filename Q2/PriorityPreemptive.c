#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
  int pid;
  int arrivalTime;
  int burstTime;
  int TATime;
  int waitTime;
  int responseTime;
  int remainingTime;
  int startTime;
  int finishTime;
  int priority;
} Process;

void PriorityPreemptive(Process *processes, int n)
{
  int currTime = 0, completed = 0;
  float totalTAT = 0, totalWT = 0, totalRT = 0;
  int lastFinish = -1;

  while (completed != n)
  {
    int idx = -1;
    int highestPriority = INT_MAX;

    for(int i = 0; i < n; i++)
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
          {
            idx = i;
          }
        }
      }
    }

    if (idx == -1)
      currTime++;
    else
    {
      if (processes[idx].remainingTime == processes[idx].burstTime)
      {
        processes[idx].startTime = currTime;
        processes[idx].responseTime = currTime - processes[idx].arrivalTime;
      }
      processes[idx].remainingTime--;
      currTime++;
      if (processes[idx].remainingTime == 0)
      {
        processes[idx].finishTime = currTime;
        processes[idx].TATime = processes[idx].finishTime - processes[idx].arrivalTime;
        processes[idx].waitTime = processes[idx].TATime - processes[idx].burstTime;
        
        totalWT += processes[idx].waitTime;
        totalTAT += processes[idx].TATime;
        totalRT += processes[idx].responseTime;
        completed++;
        lastFinish = processes[idx].finishTime;
      }
      printf("| (%d) P%d (%d) ", currTime - 1, processes[idx].pid, currTime);
    }
  }
  printf("|\n");

   printf("Observation Table:\nPID\tAT\tBT\tPRI\tST\tFT\tWT\tTAT\tRT\n");
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
      processes[i].pid = i + 1;
      processes[i].remainingTime = processes[i].burstTime;
      processes[i].startTime = 0;
      processes[i].responseTime = -1;
      processes[i].finishTime = 0;
    }
    printf("\n");

    priorityPreemptiveScheduling(processes, n);

    free(processes);
    return 0;
}
