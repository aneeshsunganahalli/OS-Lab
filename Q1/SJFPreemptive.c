#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
  int pid;
  int arrivalTime;
  int burstTime;
  int TATime;
  int finishTime;
  int startingTime;
  int remainingTime;
  int waitTime;
  int responseTime;
  int completed;
} Process;

void calculateTime(Process *processes, int n)
{
  int currTime = 0, completed_processes = 0, prev = -1;

  while (completed_processes < n)
  {
    int sji = -1, srt = INT_MAX;
    for (int i = 0; i < n; i++)
    {
      if (processes[i].arrivalTime <= currTime && !processes[i].completed)
      {
        if (processes[i].remainingTime < srt)
        {
          srt = processes[i].remainingTime;
          sji = i;
        }
        else if (processes[i].remainingTime == srt)
        {
          sji = i;
        }
      }
    }

    if (sji == -1)
      currTime++;
    else
    {
      if (prev != sji)
      {
        if (processes[sji].startingTime == -1) {
          processes[sji].startingTime = currTime;
          processes[sji].responseTime = currTime - processes[sji].arrivalTime;
        }
        prev = sji;
      }
      processes[sji].remainingTime--;
      currTime++;
      if (processes[sji].remainingTime == 0)
      {
        processes[sji].finishTime = currTime;
        processes[sji].waitTime = processes[sji].finishTime - processes[sji].burstTime - processes[sji].arrivalTime;
        processes[sji].TATime = processes[sji].finishTime - processes[sji].arrivalTime;
        processes[sji].completed = 1;
      }
      printf("| (%d) P%d (%d) ", currTime - 1, processes[sji].pid, currTime);
    }
  }
  printf("|\n");
}

void printInfo(Process *processes, int n)
{
  int totalTAT = 0, totalWT = 0, totalRT = 0;
  float avgTAT = 0, avgWT = 0, avgRT = 0;
  printf("\nProcess\tArrival\tBurst\tStart\tFinish\tTAT\tWT\tRT\n");
  for (int i = 0; i < n; i++)
  {
    printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
           processes[i].pid, processes[i].arrivalTime, processes[i].burstTime,
           processes[i].startingTime, processes[i].finishTime, 
           processes[i].TATime, processes[i].waitTime, processes[i].responseTime);
    totalTAT += processes[i].TATime;
    totalWT += processes[i].waitTime;
    totalRT += processes[i].responseTime;
  }
  avgWT = (float)totalWT / n;
  avgTAT = (float)totalTAT / n;
  avgRT = (float)totalRT / n;
  printf("\nAverage Turnaround Time: %.2f", avgTAT);
  printf("\nAverage Waiting Time: %.2f", avgWT);
  printf("\nAverage Response Time: %.2f\n", avgRT);
}

void main()
{
  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);
  Process *processes = (Process *)malloc(n * sizeof(Process));
  for (int i = 0; i < n; i++)
  {
    printf("Enter the arrival time and burst time for process %d: ", i + 1);
    processes[i].pid = i + 1;
    processes[i].completed = 0;
    processes[i].startingTime = -1;
    processes[i].responseTime = 0;
    scanf("%d%d", &processes[i].arrivalTime, &processes[i].burstTime);
    processes[i].remainingTime = processes[i].burstTime;
  }

  calculateTime(processes, n);
  printInfo(processes, n);
  free(processes);

}
