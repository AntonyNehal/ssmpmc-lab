#include <stdio.h>

struct process {
    int id, bt, at, ct, tt, wt, finish, pr;
} p[100];

int main() {
    int size, time = 0, count = 0, indx = -1;
    float avwt = 0, avtt = 0;

    // Input the number of processes
    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &size);

    // Input details of each process
    printf("\nENTER DETAILS OF PROCESSES - ARRIVAL TIME : BURST TIME : PRIORITY\n");
    for (int i = 0; i < size; i++) {
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].id = i + 1;
        p[i].finish = -1; // Process not finished initially
    }

    // Process scheduling loop
    while (count != size) {
        indx = -1; // Reset the index for each scheduling iteration
        int found = 0; // Flag to check if an eligible process is found

        // Find the process with the lowest priority that is ready to execute
        for (int i = 0; i < size; i++) {
            if (p[i].finish == -1 && p[i].at <= time) {
                // If no process is found yet or a lower priority process is found
                if (!found || p[i].pr < p[indx].pr) {
                    indx = i;
                    found = 1;
                }
            }
        }

        // No process is ready at this time, so increment time
        if (indx == -1) {
            time++;
        } else {
            // Process the selected process
            p[indx].ct = time + p[indx].bt;
            time = p[indx].ct;
            p[indx].tt = p[indx].ct - p[indx].at;
            p[indx].wt = p[indx].tt - p[indx].bt;
            p[indx].finish = 0; // Mark process as completed
            count++;
        }
    }

    // Display results
    printf("\nPROCESS ID\tARRIVAL TIME\tCOMPLETION TIME\tWAITING TIME\tTURNAROUND TIME\n\n");
    for (int i = 0; i < size; i++) {
        printf("    P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].ct, p[i].wt, p[i].tt);
        avwt += (float)p[i].wt;
        avtt += (float)p[i].tt;
    }

    printf("\n\nAVERAGE WAITING TIME : %.2f", (avwt / size));
    printf("\nAVERAGE TURNAROUND TIME : %.2f\n", (avtt / size));

    return 0;
}
