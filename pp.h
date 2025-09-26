#include <stdio.h>
#include "swap.h"
#ifndef PP_H
#define PP_H

/*---------------------------------------
  Input: asks user for number of processes,
  burst times and priorities.
  Uses 1-based indexing for consistency.
----------------------------------------*/
void input(int *priority, int n) {
    for (int i = 1; i <= n; i++) {
        printf("Enter priority for Process %d: ", i);
        if (scanf("%d", &priority[i]) != 1) {
            printf("Invalid input.\n");
            return;
        }
    }
}

/*---------------------------------------
  Sort processes by priority (descending)
----------------------------------------*/
void ppsort(int *burst, int *priority, int *index, int n) {
    for (int i = 1; i <= n; i++) {
        int maxIdx = i;
        for (int j = i + 1; j <= n; j++) {
            if (priority[j] > priority[maxIdx]) {
                maxIdx = j;
            }
        }
        swap(&priority[i], &priority[maxIdx]);
        swap(&burst[i], &burst[maxIdx]);
        swap(&index[i], &index[maxIdx]);
    }
}

/*---------------------------------------
  Priority (non-preemptive) Scheduling
----------------------------------------*/
void pp(int *burst, int *priority, int *index, int n) {
    int ct[n + 1], wt[n + 1], tat[n + 1];
    int time = 0;

    ppsort(burst, priority, index, n);

    printf("\n\nPriority Scheduling (Non-Preemptive)\n====================================\n");
    printf("Process\tBT\tPriority\tCT\tWT\tTAT\n");

    for (int i = 1; i <= n; i++) {
        ct[i]  = time + burst[i];
        wt[i]  = time;                  // waiting time before execution
        tat[i] = wt[i] + burst[i];      // turnaround time
        printf("P%d\t%d\t%d\t\t%d\t%d\t%d\n",
               index[i], burst[i], priority[i], ct[i], wt[i], tat[i]);
        time += burst[i];
    }
}

/*---------------------------------------
  Gantt Chart printer
----------------------------------------*/
void ppgantt(int *burst, int *priority, int *index, int n) {
    ppsort(burst, priority, index, n);

    printf("\n\nGantt Chart\n===========\n|");
    for (int i = 1; i <= n; i++) {
        printf("P%d", index[i]);
        for (int j = 0; j < burst[i]; j++) printf(" ");
        printf("|");
    }
    printf("\n0");
    int t = 0;
    for (int i = 1; i <= n; i++) {
        t += burst[i];
        printf("%*d", burst[i] + 2, t);   // align numbers under bars
    }
    printf("\n");
}

#endif
