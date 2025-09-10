#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int pid;
  int arrivalTime;
  int burstTime;
  int TATime;
  int finishTime;
  int startingTime;
  int waitTime;
  int responseTime;
  int completed;
} Process;

void sortByArrivalTime(Process *processes, int n)
{
  // Sort processes by arrival time using bubble sort
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
}

void calculateTime(Process *processes, int n)
{
    int currTime = 0;
    printf("\nGantt Chart:\n| ");

    for (int i = 0; i < n; i++)
    {
        // Handle idle time
        if (currTime < processes[i].arrivalTime)
        {
            printf("IDLE (%d–%d) | ", currTime, processes[i].arrivalTime);
            currTime = processes[i].arrivalTime;
        }

        // Start time & response time
        processes[i].startingTime = currTime;
        processes[i].responseTime = currTime - processes[i].arrivalTime;

        // Run the process
        currTime += processes[i].burstTime;
        processes[i].finishTime = currTime;

        // Turnaround & waiting times
        processes[i].TATime = processes[i].finishTime - processes[i].arrivalTime;
        processes[i].waitTime = processes[i].TATime - processes[i].burstTime;
        processes[i].completed = 1;

        // Print Gantt chart segment
        printf("P%d (%d–%d) | ", processes[i].pid, processes[i].startingTime, processes[i].finishTime);
    }
    printf("\n");
}


void printInfo(Process *processes, int n)
{
  int totalTAT = 0, totalWT = 0, totalRT = 0;
  float avgTAT = 0, avgWT = 0, avgRT = 0;
  
  printf("\nProcess\tArrival\tBurst\tStart\tFinish\tTAT\tWT\tRT\n");
  printf("-------\t-------\t-----\t-----\t------\t---\t--\t--\n");
  
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

int main()
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
    scanf("%d%d", &processes[i].arrivalTime, &processes[i].burstTime);
  }
  
  // Sort processes by arrival time
  sortByArrivalTime(processes, n);
  
  calculateTime(processes, n);
  printInfo(processes, n);
  
  free(processes);
  return 0;
}
