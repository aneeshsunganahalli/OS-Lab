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
        processes[sji].startingTime = processes[sji].startingTime == -1 ? currTime : processes[sji].startingTime;
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
  print("|\n");
}

void printInfo(Process *processes, int n)
{
  int totalTAT = 0, totalWT = 0;
  float avgTAT = 0, avgWT = 0;
  printf("");
  for (int i = 0; i < n; i++)
  {
    printf("");
    totalTAT += processes[i].TATime;
    totalWT += processes[i].waitTime;
  }
  avgWT = totalWT / n;
  avgTAT = totalTAT / n;
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
    scanf("%d%d", &processes[i].arrivalTime, &processes[i].burstTime);
    processes[i].remainingTime = processes[i].burstTime;
  }

  calculateTime(processes, n);
  printInfo(processes, n);
  free(processes);
}