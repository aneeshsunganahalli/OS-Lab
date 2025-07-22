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
  int remainingTime;
  int waitTime;
  int responseTime;
  int completed;
} Process;

void calculateTime(Process *processes, int n, int timeQuantum)
{
  int currTime = 0, completed_processes = 0;
  int queue[100], front = 0, rear = 0;
  int inQueue[100] = {0}; // Track which processes are in queue
  
  // Add processes that arrive at time 0 to queue
  for (int i = 0; i < n; i++)
  {
    if (processes[i].arrivalTime <= currTime)
    {
      queue[rear++] = i;
      inQueue[i] = 1;
    }
  }
  
  printf("Gantt Chart:\n");
  printf("| ");
  
  while (completed_processes < n)
  {
    if (front == rear)
    {
      // No process in queue, advance time
      currTime++;
      // Add newly arrived processes
      for (int i = 0; i < n; i++)
      {
        if (processes[i].arrivalTime <= currTime && !processes[i].completed && !inQueue[i])
        {
          queue[rear++] = i;
          inQueue[i] = 1;
        }
      }
      continue;
    }
    
    int current = queue[front++];
    inQueue[current] = 0;
    
    // Set starting time and response time if first time
    if (processes[current].startingTime == -1)
    {
      processes[current].startingTime = currTime;
      processes[current].responseTime = currTime - processes[current].arrivalTime;
    }
    
    // Execute for time quantum or remaining time, whichever is smaller
    int execTime = (processes[current].remainingTime < timeQuantum) ? 
                   processes[current].remainingTime : timeQuantum;
    
    processes[current].remainingTime -= execTime;
    currTime += execTime;
    
    printf("P%d (%d) | ", processes[current].pid, currTime);
    
    // Add newly arrived processes to queue
    for (int i = 0; i < n; i++)
    {
      if (processes[i].arrivalTime <= currTime && !processes[i].completed && !inQueue[i])
      {
        queue[rear++] = i;
        inQueue[i] = 1;
      }
    }
    
    // Check if process is completed
    if (processes[current].remainingTime == 0)
    {
      processes[current].finishTime = currTime;
      processes[current].TATime = processes[current].finishTime - processes[current].arrivalTime;
      processes[current].waitTime = processes[current].TATime - processes[current].burstTime;
      processes[current].completed = 1;
      completed_processes++;
    }
    else
    {
      // Add back to queue if not completed
      queue[rear++] = current;
      inQueue[current] = 1;
    }
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
  int n, timeQuantum;
  
  printf("Enter number of processes: ");
  scanf("%d", &n);
  
  printf("Enter time quantum: ");
  scanf("%d", &timeQuantum);
  
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
  
  calculateTime(processes, n, timeQuantum);
  printInfo(processes, n);
  
  free(processes);
  return 0;
}
