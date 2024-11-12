#include <stdio.h>

int main() {
    int q[100], front = -1, rear = -1;
    int n, id[20], at[20], bt[20], left[20], ct[20], wt[20], tt[20], status[20];
    int current_time = 0, process_index, completed_processes = 0, time_quantum;

    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);
    printf("\nENTER DETAILS OF PROCESSES - PROCESS ID : ARRIVAL TIME : BURST TIME\n");

    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &id[i], &at[i], &bt[i]);
        left[i] = bt[i];
        status[i] = 0;  // Status 0 means process not yet in the queue
    }

    printf("\nENTER THE TIME QUANTUM: ");
    scanf("%d", &time_quantum);

    while (completed_processes < n) {
        // Check if any processes need to be added to the queue based on current time
        for (int j = 0; j < n; j++) {
            if (status[j] == 0 && at[j] <= current_time) {
                // Enqueue
                if (front == -1 && rear == -1) {
                    front = 0;
                }
                rear++;
                q[rear] = j;
                status[j] = 1;  // Status 1 means process is in the queue
            }
        }

        if (front == -1) {
            // No process in queue, increment current time
            current_time++;
        } else {
            // Dequeue
            process_index = q[front];
            if (front == rear) {
                front = -1;
                rear = -1;
            } else {
                front++;
            }

            if (left[process_index] <= time_quantum) {
                // Process completes in this time slice
                current_time += left[process_index];
                ct[process_index] = current_time;
                tt[process_index] = current_time - at[process_index];
                wt[process_index] = tt[process_index] - bt[process_index];
                status[process_index] = 2;  // Status 2 means process is completed
                completed_processes++;
            } else {
                // Process needs more time, only part of it is completed in this time slice
                current_time += time_quantum;
                left[process_index] -= time_quantum;

                // Re-check the queue for any new arrivals during this time slice
                for (int j = 0; j < n; j++) {
                    if (status[j] == 0 && at[j] <= current_time) {
                        // Enqueue new process
                        if (front == -1 && rear == -1) {
                            front = 0; 
                        }
                        rear++;
                        q[rear] = j;
                        status[j] = 1;
                    }
                }

                // Re-enqueue the current process
                if (front == -1 && rear == -1) {
                    front = 0;
                }
                rear++;
                q[rear] = process_index;
            }
        }
    }

    // Display the results
    float avwt = 0, avtt = 0;
    printf("\nPROCESS ID\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
    for (int i = 0; i < n; i++) {
        printf("   %d\t\t\t%d\t\t\t%d\t\t\t%d\n", id[i], ct[i], wt[i], tt[i]);
        avwt += (float)wt[i];
        avtt += (float)tt[i];
    }
    printf("\n\nAVERAGE WAITING TIME : %.2f", (avwt / (float)n));
    printf("\nAVERAGE TURNAROUND TIME : %.2f\n", (avtt / (float)n));


    return 0;
}
