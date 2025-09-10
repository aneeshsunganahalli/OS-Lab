#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
  int pid;
  int AT;       // Arrival Time
  int BT;       // Burst Time
  int CT;       // Completion Time
  int TAT;      // Turnaround Time
  int WT;       // Waiting Time
  int RT;       // Response Time
  int remT;     // Remaining Time
  int priority; // Lower number = higher priority
  int startTime;
} Process;

void PriorityPreemptive(Process *processes, int n)
{
  int currTime = 0, completed = 0;
  float totalTAT = 0, totalWT = 0, totalRT = 0;
  int prevIdx = -1, start = 0;

  printf("\nGantt Chart:\n");

  while (completed != n)
  {
    int idx = -1, highestPriority = INT_MAX;

    for (int i = 0; i < n; i++)
    {
      if (processes[i].AT <= currTime && processes[i].remT > 0)
      {
        if (processes[i].priority < highestPriority)
        {
          highestPriority = processes[i].priority;
          idx = i;
        }
        else if (processes[i].priority == highestPriority)
        {
          if (processes[i].AT < processes[idx].AT)
            idx = i;
        }
      }
    }

    if (idx == -1)
    {
      currTime++;
      continue;
    }

    if (prevIdx != idx)
    {
      if (prevIdx != -1)
      {
        printf("P%d (%d - %d) | ", processes[prevIdx].pid, start, currTime);
      }
      start = currTime;
      prevIdx = idx;
    }

    if (processes[idx].remT == processes[idx].BT)
    {
      processes[idx].startTime = currTime;
      processes[idx].RT = currTime - processes[idx].AT;
    }

    processes[idx].remT--;
    currTime++;

    if (processes[idx].remT == 0)
    {
      processes[idx].CT = currTime;
      processes[idx].TAT = processes[idx].CT - processes[idx].AT;
      processes[idx].WT = processes[idx].TAT - processes[idx].BT;
      completed++;

      totalWT += processes[idx].WT;
      totalRT += processes[idx].RT;
      totalTAT += processes[idx].TAT;
    }
  }

  // Print last process interval
  if (prevIdx != -1)
  {
    printf("P%d (%d - %d) |", processes[prevIdx].pid, start, currTime);
  }
  printf("\n");

  printf("\nObservation Table:\n");
  printf("PID\tAT\tBT\tPRI\tST\tCT\tWT\tTAT\tRT\n");
  for (int i = 0; i < n; i++)
  {
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
           processes[i].pid, processes[i].AT, processes[i].BT,
           processes[i].priority, processes[i].startTime, processes[i].CT,
           processes[i].WT, processes[i].TAT, processes[i].RT);
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

  printf("Enter AT, BT, Priority for each process:\n");
  for (int i = 0; i < n; i++)
  {
    processes[i].pid = i + 1;
    scanf("%d %d %d", &processes[i].AT, &processes[i].BT, &processes[i].priority);
    processes[i].remT = processes[i].BT;
    processes[i].startTime = 0;
    processes[i].RT = -1;
    processes[i].CT = 0;
  }

  PriorityPreemptive(processes, n);

  free(processes);
  return 0;
}
