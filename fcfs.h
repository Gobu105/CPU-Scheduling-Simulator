#ifndef FCFS_H
#define FCFS_H
#include <stdio.h>
#include "gantt_utils.h"
// -------------------- Data Structure --------------------
typedef struct {
    int pid;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
} FCFSProcess;

// -------------------- FCFS with Gantt Chart --------------------
static inline void calculateFCFS(FCFSProcess p[], int n)
{
    int time = 0;

    printf("\n\nGantt Chart\n===========\n");

    for (int i = 0; i < n; i++) {
        // If CPU is idle before this process arrives
        if (time < p[i].arrival) {
            printf("|idle");
            int idle_time = p[i].arrival - time;
            for (int k = 0; k < idle_time; k++) printf(" ");
            time = p[i].arrival;
        }

        printf("|P%d", p[i].pid);
        for (int k = 0; k < p[i].burst; k++) printf(" ");
        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;
    }
    printf("|\n");
}

static inline void displayFCFSTable(FCFSProcess p[], int n)
{
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].waiting, p[i].turnaround);
    }
}

#endif // FCFS_H
