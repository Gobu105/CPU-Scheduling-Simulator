#ifndef SJF_H
#define SJF_H
#include <stdio.h>
#include "gantt_utils.h"

typedef struct {
    int pid, arrival, burst;
    int waiting, turnaround;
    int completed;
} SJFProcess;

static inline void calculateSJF(SJFProcess p[], int n)
{
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) p[i].completed = 0;

    printf("\n\nGantt Chart\n===========\n");

    while (completed < n) {
        int idx = -1, min_burst = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= time) {
                if (p[i].burst < min_burst) {
                    min_burst = p[i].burst;
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

static inline void displaySJFTable(SJFProcess p[], int n)
{
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].waiting, p[i].turnaround);
}

#endif // SJF_H
