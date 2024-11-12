#include <stdio.h>

struct process {
    int id, bt, ct, at, tt, wt;
} p[100], temp;

int main() {
    int i, j, n, time = 0, index;
    float avgtt = 0, avgwt = 0;
    
    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    // Input arrival time and burst time for each process
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
    }
    
    // Sort processes by arrival time (FCFS for processes that arrive first)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    
    // SJF Scheduling logic
    for (i = 0; i < n; i++) {
        index = i;
        
        // Find the process with the shortest burst time among the arrived processes
        for (j = i + 1; j < n && p[j].at <= time; j++) {
            if (p[index].bt > p[j].bt) {
                index = j;
            }
        }
        
        // Swap to schedule the shortest job next
        temp = p[i];
        p[i] = p[index];
        p[index] = temp;
        
        // Update time if CPU is idle until process arrival
        if (time < p[i].at) {
            time = p[i].at;
        }
        
        // Calculate completion time, turnaround time, and waiting time
        time += p[i].bt;         // Update cumulative time
        p[i].ct = time;          // Set completion time
        p[i].tt = p[i].ct - p[i].at; // Turnaround time = completion - arrival
        p[i].wt = p[i].tt - p[i].bt; // Waiting time = turnaround - burst
    }
    
    // Display the process information
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("   %d\t      %d\t          %d\t               %d\t           %d\t              %d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tt);
    }
    
    // Calculate average waiting and turnaround times
    for (i = 0; i < n; i++) {
        avgtt += (float)p[i].tt; // Explicitly cast to float
        avgwt += (float)p[i].wt; // Explicitly cast to float
    }
    
    printf("\nAverage waiting time: %.2f\n", avgwt / (float)n);
    printf("Average turnaround time: %.2f\n", avgtt / (float)n);

    return 0;
}
