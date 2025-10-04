
/* ========================= fcfs.h ========================= */
#ifndef FCFS_H
#define FCFS_H
#include "utils.h"

void fcfs(Process input[], int n) {
    print_header("FCFS (First Come First Serve)");
    Process *procs = copy_procs(input, n);
    /* sort by arrival, then pid */
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j) {
            if (procs[i].at > procs[j].at || (procs[i].at == procs[j].at && procs[i].pid > procs[j].pid)) {
                Process tmp = procs[i]; procs[i] = procs[j]; procs[j] = tmp;
            }
        }
    int time = 0;
    for (int i = 0; i < n; ++i) {
        if (time < procs[i].at) time = procs[i].at; /* idle till arrival */
        procs[i].start_time = time;
        time += procs[i].bt;
        procs[i].completion_time = time;
        procs[i].tat = procs[i].completion_time - procs[i].at;
        procs[i].wt = procs[i].tat - procs[i].bt;
        procs[i].resp = procs[i].start_time - procs[i].at;
    }
    printf("\n");
    print_table(procs, n, 0);
    free(procs);
}
void fcfsgantt(Process input[], int n){
    print_header("FCFS (First Come First Serve)");
    Process *procs = copy_procs(input, n);
    /* sort by arrival, then pid */
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j) {
            if (procs[i].at > procs[j].at || (procs[i].at == procs[j].at && procs[i].pid > procs[j].pid)) {
                Process tmp = procs[i]; procs[i] = procs[j]; procs[j] = tmp;
            }
        }
    int time = 0;
    printf("Gantt Chart:\n");
    for (int i = 0; i < n; ++i) {
        if (time < procs[i].at) time = procs[i].at; /* idle till arrival */
        procs[i].start_time = time;
        print_gantt_pair(procs[i].pid, procs[i].start_time, procs[i].start_time + procs[i].bt);
	time += procs[i].bt;
        procs[i].completion_time = time;
        procs[i].tat = procs[i].completion_time - procs[i].at;
        procs[i].wt = procs[i].tat - procs[i].bt;
        procs[i].resp = procs[i].start_time - procs[i].at;
    }
    printf("|\n");
    free(procs);
}
void fcfsaverage(Process input[], int n){
    print_header("FCFS (First Come First Serve)");
    Process *procs = copy_procs(input, n);
    /* sort by arrival, then pid */
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j) {
            if (procs[i].at > procs[j].at || (procs[i].at == procs[j].at && procs[i].pid > procs[j].pid)) {
                Process tmp = procs[i]; procs[i] = procs[j]; procs[j] = tmp;
            }
        }
    int time = 0;
    for (int i = 0; i < n; ++i) {
        if (time < procs[i].at) time = procs[i].at; /* idle till arrival */
        procs[i].start_time = time;
        time += procs[i].bt;
        procs[i].completion_time = time;
        procs[i].tat = procs[i].completion_time - procs[i].at;
        procs[i].wt = procs[i].tat - procs[i].bt;
        procs[i].resp = procs[i].start_time - procs[i].at;
    }
    printf("\n");
    print_average(procs,n);
    printf("\n");
    free(procs);
}
#endif /* FCFS_H */
