#ifndef PP_H
#define PP_H
#include <stdio.h>
#include "gantt_utils.h"

// -------------------- Data Structure --------------------
typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time (original)
    int remaining;  // Remaining burst time
    int priority;   // Lower number = higher priority
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int completed;  // Flag to mark completion
} PPProcess;

// -------------------- Preemptive Priority Scheduling --------------------
static inline void calculatePP(PPProcess p[], int n)
{
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].completed = 0;
    }

    printf("\n\nGantt Chart\n===========\n");

    while (completed < n) {
        int idx = -1;
        int bestPriority = 1e9;

        // Select ready process with highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= time) {
                if (p[i].priority < bestPriority) {
                    bestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // CPU idle until next process arrives
            int next_arrival = 1e9;
            for (int i = 0; i < n; i++)
                if (!p[i].completed && p[i].arrival < next_arrival)
                    next_arrival = p[i].arrival;

            printf("|idle");
            for (int k = 0; k < next_arrival - time; k++) printf(" ");
            time = next_arrival;
            continue;
        }

        // Run selected process for 1 time unit
        printf("|P%d", p[idx].pid);
        p[idx].remaining--;
        time++;

        // If process finishes
        if (p[idx].remaining == 0) {
            p[idx].completed = 1;
            completed++;
            p[idx].turnaround = time - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
        }
    }
    printf("|\n");
}

// -------------------- Display Results --------------------
static inline void displayPPTable(PPProcess p[], int n)
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

#endif // PP_H
