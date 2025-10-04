
/* ========================= sjf.h (non-preemptive SJF) ========================= */
#ifndef SJF_H
#define SJF_H
#include "utils.h"

void sjf(Process input[], int n) {
    print_header("SJF (Non-preemptive)");
    Process *procs = copy_procs(input, n);
    int done = 0, time = 0;
    int completed[n]; memset(completed, 0, sizeof(completed));
    while (done < n) {
        int idx = -1; int min_bt = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && procs[i].at <= time) {
                if (procs[i].bt < min_bt || (procs[i].bt == min_bt && procs[i].at < procs[idx].at)) { min_bt = procs[i].bt; idx = i; }
            }
        }
        if (idx == -1) { time++; continue; }
        procs[idx].start_time = time;
        time += procs[idx].bt;
        procs[idx].completion_time = time;
        procs[idx].tat = procs[idx].completion_time - procs[idx].at;
        procs[idx].wt = procs[idx].tat - procs[idx].bt;
        procs[idx].resp = procs[idx].start_time - procs[idx].at;
        completed[idx] = 1; done++;
    }
    printf("\n");
    print_table(procs, n, 0);
    free(procs);
}

void sjfgantt(Process input[], int n){
    print_header("SJF (Non-preemptive)");
    Process *procs = copy_procs(input, n);
    int done = 0, time = 0;
    int completed[n]; memset(completed, 0, sizeof(completed));
    printf("Gantt Chart:\n");
    while (done < n) {
        int idx = -1; int min_bt = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && procs[i].at <= time) {
                if (procs[i].bt < min_bt || (procs[i].bt == min_bt && procs[i].at < procs[idx].at)) { min_bt = procs[i].bt; idx = i; }
            }
        }
        if (idx == -1) { time++; continue; }
        procs[idx].start_time = time;
        print_gantt_pair(procs[idx].pid, time, time + procs[idx].bt);
        time += procs[idx].bt;
        procs[idx].completion_time = time;
        procs[idx].tat = procs[idx].completion_time - procs[idx].at;
        procs[idx].wt = procs[idx].tat - procs[idx].bt;
        procs[idx].resp = procs[idx].start_time - procs[idx].at;
        completed[idx] = 1; done++;
    }
    printf("|\n");
    free(procs);
}

void sjfaverage(Process input[], int n){
    print_header("SJF (Non-preemptive)");
    Process *procs = copy_procs(input, n);
    int done = 0, time = 0;
    int completed[n]; memset(completed, 0, sizeof(completed));
    while (done < n) {
        int idx = -1; int min_bt = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && procs[i].at <= time) {
                if (procs[i].bt < min_bt || (procs[i].bt == min_bt && procs[i].at < procs[idx].at)) { min_bt = procs[i].bt; idx = i; }
            }
        }
        if (idx == -1) { time++; continue; }
        procs[idx].start_time = time;
        time += procs[idx].bt;
        procs[idx].completion_time = time;
        procs[idx].tat = procs[idx].completion_time - procs[idx].at;
        procs[idx].wt = procs[idx].tat - procs[idx].bt;
        procs[idx].resp = procs[idx].start_time - procs[idx].at;
        completed[idx] = 1; done++;
    }
    printf("\n");
    print_average(procs, n);
    printf("\n");
    free(procs);
}

#endif /* SJF_H */
