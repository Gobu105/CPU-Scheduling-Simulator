

/* ========================= utils.h ========================= */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int pid;
    int at;    /* Arrival Time */
    int bt;    /* Burst Time */
    int rt_time; /* Remaining Time (used in preemptive algos) */
    int priority; /* lower value -> higher priority */

    /* computed */
    int start_time; /* first time the process gets CPU */
    int completion_time;
    int tat; /* Turnaround time */
    int wt;  /* Waiting time */
    int resp; /* Response time */
} Process;

/* Helpers */
void print_header(const char *name) {
    printf("\n================ %s ================\n", name);
}

void print_gantt_pair(int pid, int s, int e) {
    printf("| P%d (%d-%d) ", pid, s, e);
}

void print_table(Process procs[], int n, int with_priority) {
    int i;
    double total_wt = 0, total_tat = 0, total_rt = 0;
    if (with_priority) {
        printf("\nPID\tAT\tBT\tPR\tST\tCT\tTAT\tWT\tRT\n");
    } else {
        printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    }
    for (i = 0; i < n; ++i) {
        if (with_priority) printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", procs[i].pid, procs[i].at, procs[i].bt, procs[i].priority, procs[i].start_time, procs[i].completion_time, procs[i].tat, procs[i].wt, procs[i].resp);
        else printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", procs[i].pid, procs[i].at, procs[i].bt, procs[i].start_time, procs[i].completion_time, procs[i].tat, procs[i].wt, procs[i].resp);
    }
}

/* Copy processes array */
Process *copy_procs(Process src[], int n) {
    Process *dst = malloc(sizeof(Process) * n);
    for (int i = 0; i < n; ++i) dst[i] = src[i];
    return dst;
}

/* Average Time Calculator */
void print_average(Process procs[], int n){
    int i;
    double total_wt = 0, total_tat = 0, total_rt = 0;
    for (i = 0; i < n; ++i) {
        total_wt += procs[i].wt;
        total_tat += procs[i].tat;
        total_rt += procs[i].resp;
    }
    printf("\nAvg WT = %.2f\nAvg TAT = %.2f\nAvg RT = %.2f\n", total_wt / n, total_tat / n, total_rt / n);
}

#endif /* UTILS_H */
