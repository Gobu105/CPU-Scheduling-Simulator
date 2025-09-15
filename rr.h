#ifndef RR_H
#define RR_H
#include <stdio.h>
#include "gantt_utils.h"

// -------------------- Data Structure --------------------
typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time (original)
    int remaining;  // Remaining burst time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int completed;  // 1 if finished
} RRProcess;

// -------------------- Round Robin Scheduling --------------------
static inline void calculateRR(RRProcess p[], int n, int quantum)
{
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].completed = 0;
    }

    printf("\n\nGantt Chart\n===========\n");

    // We'll iterate until all processes are complete
    while (completed < n) {
        int progress = 0;    // Did we run any process in this full cycle?

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= time) {
                progress = 1;

                int slice = (p[i].remaining > quantum) ? quantum : p[i].remaining;

                printf("|P%d", p[i].pid);
                for (int k = 0; k < slice; k++) printf(" ");

                p[i].remaining -= slice;
                time += slice;

                if (p[i].remaining == 0) {
                    p[i].completed = 1;
                    completed++;
                    p[i].turnaround = time - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                }
            }
        }

        // If no process was ready in this pass → CPU idle until next arrival
        if (!progress) {
            int next_arrival = 1e9;
            for (int i = 0; i < n; i++)
                if (!p[i].completed && p[i].arrival < next_arrival)
                    next_arrival = p[i].arrival;

            printf("|idle");
            for (int k = 0; k < next_arrival - time; k++) printf(" ");
            time = next_arrival;
        }
    }
    printf("|\n");
}

// -------------------- Display Results --------------------
static inline void displayRRTable(RRProcess p[], int n)
{
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].waiting,
               p[i].turnaround);
    }
}

#endif // RR_H
