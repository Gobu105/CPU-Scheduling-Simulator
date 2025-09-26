#ifndef PNP_H
#define PNP_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Preemptive Priority Scheduling
void pnp(int *arrival, int *burst, int *priority,
         int *index, int n, int **timeline, int *tlen)
{
    int remaining[n + 1], completion[n + 1], turnaround[n + 1], waiting[n + 1];
    for (int i = 1; i <= n; i++) {
        remaining[i]  = burst[i];
        completion[i] = 0;
    }

    double total_tat = 0, total_wt = 0;
    int completed = 0;

    int capacity = 1000;
    int *tl = malloc(sizeof(int) * capacity);
    int len = 0;

    // Start from earliest arrival
    int earliest = INT_MAX;
    for (int i = 1; i <= n; i++)
        if (arrival[i] < earliest) earliest = arrival[i];
    int time = earliest;

    while (completed < n) {
        int idx = -1, bestPriority = INT_MAX;

        // Pick process with lowest priority number
        for (int i = 1; i <= n; i++) {
            if (arrival[i] <= time && remaining[i] > 0) {
                if (priority[i] < bestPriority ||
                    (priority[i] == bestPriority && arrival[i] < arrival[idx]) ||
                    (priority[i] == bestPriority && arrival[i] == arrival[idx] &&
                     burst[i] < burst[idx])) {
                    bestPriority = priority[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) { // CPU idle
            int next = INT_MAX;
            for (int i = 1; i <= n; i++)
                if (remaining[i] > 0 && arrival[i] < next) next = arrival[i];

            while (time < next) {
                if (len >= capacity) {
                    capacity *= 2;
                    tl = realloc(tl, sizeof(int) * capacity);
                }
                tl[len++] = -1;
                time++;
            }
            continue;
        }

        // Run chosen process for 1 time unit
        remaining[idx]--;
        if (len >= capacity) {
            capacity *= 2;
            tl = realloc(tl, sizeof(int) * capacity);
        }
        tl[len++] = idx;
        time++;

        if (remaining[idx] == 0) {
            completion[idx] = time;
            turnaround[idx] = completion[idx] - arrival[idx];
            waiting[idx]    = turnaround[idx] - burst[idx];
            total_tat += turnaround[idx];
            total_wt  += waiting[idx];
            completed++;
        }
    }

    // Print table
    printf("\nPre-emptive Priority Scheduling (PNP)\n");
    printf("Process | Arrival | Burst | Priority | Completion | Turnaround | Waiting\n");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 1; i <= n; i++) {
        printf("  P%-3d  | %-7d| %-5d| %-8d| %-10d| %-10d| %-7d\n",
               index[i], arrival[i], burst[i], priority[i],
               completion[i], turnaround[i], waiting[i]);
    }
    printf("-------------------------------------------------------------------------\n");
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
    printf("Average Waiting Time    = %.2f\n", total_wt / n);

    *timeline = tl;
    *tlen = len;
}

// Print Gantt chart from timeline
void pnpgantt(int *timeline, int len)
{
    printf("\nGantt Chart:\nTime ");
    for (int i = 0; i <= len; i++)
        printf("%4d", i);
    printf("\nProc ");
    for (int i = 0; i < len; i++) {
        if (timeline[i] == -1) printf("  ID "); // Idle
        else                   printf("  P%-2d", timeline[i]);
    }
    printf("\n");
}

#endif

