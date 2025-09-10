#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid, AT, BT, CT, TAT, WT, RT, remT, startTime, completed;
} Process;

void RoundRobin(Process *processes, int n, int timeQuantum) {
    int currTime = 0, completedProcesses = 0;
    int queue[100], front = 0, rear = 0;
    int inQueue[100] = {0};
    
    // Initially enqueue processes that have arrived at time 0
    for (int i = 0; i < n; i++) {
        if (processes[i].AT <= currTime) {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }
    
    printf("\nGantt Chart:\n| ");
    
    while (completedProcesses < n) {
        // If queue is empty, advance time to next arrival
        if (front == rear) {
            // Find the next process that will arrive
            int nextArrival = -1;
            for (int i = 0; i < n; i++) {
                if (!processes[i].completed && processes[i].AT > currTime) {
                    if (nextArrival == -1 || processes[i].AT < processes[nextArrival].AT) {
                        nextArrival = i;
                    }
                }
            }
            if (nextArrival != -1) {
                currTime = processes[nextArrival].AT;
            }
            
            // Enqueue all processes that have arrived by this time
            for (int i = 0; i < n; i++) {
                if (processes[i].AT <= currTime && !processes[i].completed && !inQueue[i]) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
            continue;
        }
        
        int current = queue[front++];
        inQueue[current] = 0;
        
        // Set start time if this is the first execution
        if (processes[current].startTime == -1) {
            processes[current].startTime = currTime;
            processes[current].RT = currTime - processes[current].AT;
        }
        
        // Execute for time quantum or remaining time, whichever is smaller
        int execTime = (processes[current].remT > timeQuantum) ? timeQuantum : processes[current].remT;
        processes[current].remT -= execTime;
        currTime += execTime;
        
        printf("P%d (%d) | ", processes[current].pid, currTime);
        
        // Enqueue new arrivals that came during or after this execution
        for (int i = 0; i < n; i++) {
            if (processes[i].AT <= currTime && !processes[i].completed && !inQueue[i] && i != current) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }
        
        // Check if current process is completed
        if (processes[current].remT == 0) {
            processes[current].CT = currTime;
            processes[current].TAT = processes[current].CT - processes[current].AT;
            processes[current].WT = processes[current].TAT - processes[current].BT;
            processes[current].completed = 1;
            completedProcesses++;
        } else {
            // Re-queue the current process if not completed
            queue[rear++] = current;
            inQueue[current] = 1;
        }
    }
    printf("\n");
}

void printInfo(Process *processes, int n) {
    int totalTAT = 0, totalWT = 0, totalRT = 0;
    
    printf("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    printf("-------\t--\t--\t--\t--\t---\t--\t--\n");
    
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid, processes[i].AT, processes[i].BT,
               processes[i].startTime, processes[i].CT,
               processes[i].TAT, processes[i].WT, processes[i].RT);
        totalTAT += processes[i].TAT;
        totalWT += processes[i].WT;
        totalRT += processes[i].RT;
    }
    
    printf("\nAverage Turnaround Time: %.2f", (float)totalTAT / n);
    printf("\nAverage Waiting Time: %.2f", (float)totalWT / n);
    printf("\nAverage Response Time: %.2f\n", (float)totalRT / n);
}

int main() {
    int n, timeQuantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);
    
    Process *processes = (Process *)malloc(n * sizeof(Process));
    
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for process %d: ", i + 1);
        processes[i].pid = i + 1;
        scanf("%d%d", &processes[i].AT, &processes[i].BT);
        processes[i].remT = processes[i].BT;
        processes[i].startTime = -1;
        processes[i].RT = 0;
        processes[i].CT = 0;
        processes[i].completed = 0;
        processes[i].TAT = 0;
        processes[i].WT = 0;
    }
    
    RoundRobin(processes, n, timeQuantum);
    printInfo(processes, n);
    
    free(processes);
    return 0;
}
