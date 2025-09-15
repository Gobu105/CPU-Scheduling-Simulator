#ifndef SRT_H
#define SRT_H
#include <stdio.h>
#include "gantt_utils.h"

typedef struct {
    int pid, arrival, burst;
    int remaining;
    int waiting, turnaround;
    int completed;
} SRTProcess;

static inline void calculateSRT(SRTProcess p[], int n)
{
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].completed = 0;
    }

    printf("\n\nGantt Chart\n===========\n");

    while (completed < n) {
        int idx = -1, min_rem = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= time) {
                if (p[i].remaining < min_rem) {
                    min_rem = p[i].remaining;
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

        // One time unit execution of shortest remaining job
        printf("|P%d", p[idx].pid);
        p[idx].remaining--;
        time++;

        if (p[idx].remaining == 0) {
            p[idx].completed = 1;
            completed++;
            p[idx].turnaround = time - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
        }
    }
    printf("|\n");
}

static inline void displaySRTTable(SRTProcess p[], int n)
{
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].waiting, p[i].turnaround);
}

#endif // SRT_H
