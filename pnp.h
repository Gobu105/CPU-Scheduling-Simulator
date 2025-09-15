#ifndef PNP_H
#define PNP_H
#include <stdio.h>
#include "gantt_utils.h"

// -------------------- Data Structure --------------------
typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int priority;   // Lower number = higher priority
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int completed;  // Flag to mark completion
} PNPProcess;

// -------------------- Priority (Non-Preemptive) Scheduling --------------------
static inline void calculatePNP(PNPProcess p[], int n)
{
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) p[i].completed = 0;

    printf("\n\nGantt Chart\n===========\n");

    while (completed < n) {
        int idx = -1;
        int bestPriority = 1e9;

        // choose highest priority (lowest number) among arrived processes
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= time) {
                if (p[i].priority < bestPriority) {
                    bestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // CPU idle until next arrival
            int next_arrival = 1e9;
            for (int i = 0; i < n; i++)
                if (!p[i].completed && p[i].arrival < next_arrival)
                    next_arrival = p[i].arrival;

            printf("|idle");
            for (int k = 0; k < next_arrival - time; k++) printf(" ");
            time = next_arrival;
            continue;
        }

        // Run selected process to completion (non-preemptive)
        printf("|P%d", p[idx].pid);
        for (int k = 0; k < p[idx].burst; k++) printf(" ");

        p[idx].waiting = time - p[idx].arrival;
        time += p[idx].burst;
        p[idx].turnaround = p[idx].waiting + p[idx].burst;
        p[idx].completed = 1;
        completed++;
    }
    printf("|\n");
}

// -------------------- Display Results --------------------
static inline void displayPNPTable(PNPProcess p[], int n)
{
    printf("\nPID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].priority,
               p[i].waiting,
               p[i].turnaround);
    }
}

#endif // PNP_H
