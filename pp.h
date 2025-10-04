

/* ========================= pp.h (Preemptive Priority) ========================= */
#ifndef PP_H
#define PP_H
#include "utils.h"

void pp(Process input[], int n) {
    print_header("PP (Preemptive Priority - lower value indicates higher priority)");
    Process *procs = copy_procs(input, n);
    for (int i = 0; i < n; ++i) procs[i].rt_time = procs[i].bt, procs[i].start_time = -1;
    int completed = 0, time = 0;
    int prev_pid = -1, seg_start = -1;
    while (completed < n) {
        int idx = -1; int best_pr = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (procs[i].at <= time && procs[i].rt_time > 0) {
                if (procs[i].priority < best_pr || (procs[i].priority == best_pr && procs[i].at < procs[idx].at)) { best_pr = procs[i].priority; idx = i; }
            }
        }
        if (idx == -1) { time++; continue; }
        if (procs[idx].start_time == -1) procs[idx].start_time = time;
        if (prev_pid != procs[idx].pid) {
            if (prev_pid != -1)
            prev_pid = procs[idx].pid; seg_start = time;
        }
        procs[idx].rt_time -= 1; time++;
        if (procs[idx].rt_time == 0) {
            procs[idx].completion_time = time;
            procs[idx].tat = procs[idx].completion_time - procs[idx].at;
            procs[idx].wt = procs[idx].tat - procs[idx].bt;
            procs[idx].resp = procs[idx].start_time - procs[idx].at;
            completed++;
	    prev_pid = -1; seg_start = -1;
        }
    }
    printf("\n");
    print_table(procs, n, 1);
    free(procs);
}

void ppgantt(Process input[], int n){
    print_header("PP (Preemptive Priority - lower value indicates higher priority)");
    Process *procs = copy_procs(input, n);
    for (int i = 0; i < n; ++i) procs[i].rt_time = procs[i].bt, procs[i].start_time = -1;
    int completed = 0, time = 0;
    printf("Gantt Chart:\n");
    int prev_pid = -1, seg_start = -1;
    while (completed < n) {
        int idx = -1; int best_pr = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (procs[i].at <= time && procs[i].rt_time > 0) {
                if (procs[i].priority < best_pr || (procs[i].priority == best_pr && procs[i].at < procs[idx].at)) { best_pr = procs[i].priority; idx = i; }
            }
        }
        if (idx == -1) { time++; continue; }
        if (procs[idx].start_time == -1) procs[idx].start_time = time;
        if (prev_pid != procs[idx].pid) {
            if (prev_pid != -1) print_gantt_pair(prev_pid, seg_start, time);
            prev_pid = procs[idx].pid; seg_start = time;
        }
        procs[idx].rt_time -= 1; time++;
        if (procs[idx].rt_time == 0) {
            procs[idx].completion_time = time;
            procs[idx].tat = procs[idx].completion_time - procs[idx].at;
            procs[idx].wt = procs[idx].tat - procs[idx].bt;
            procs[idx].resp = procs[idx].start_time - procs[idx].at;
            completed++;

            print_gantt_pair(procs[idx].pid, seg_start, time);
            prev_pid = -1; seg_start = -1;
        }
    }
    printf("|\n");
    free(procs);
}

void ppaverage(Process input[], int n){
    print_header("PP (Preemptive Priority - lower value indicates higher priority)");
    Process *procs = copy_procs(input, n);
    for (int i = 0; i < n; ++i) procs[i].rt_time = procs[i].bt, procs[i].start_time = -1;
    int completed = 0, time = 0;
    int prev_pid = -1, seg_start = -1;
    while (completed < n) {
        int idx = -1; int best_pr = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (procs[i].at <= time && procs[i].rt_time > 0) {
                if (procs[i].priority < best_pr || (procs[i].priority == best_pr && procs[i].at < procs[idx].at)) { best_pr = procs[i].priority; idx = i; }
            }
        }
        if (idx == -1) { time++; continue; }
        if (procs[idx].start_time == -1) procs[idx].start_time = time;
        if (prev_pid != procs[idx].pid) {
            if (prev_pid != -1)
            prev_pid = procs[idx].pid; seg_start = time;
        }
        procs[idx].rt_time -= 1; time++;
        if (procs[idx].rt_time == 0) {
            procs[idx].completion_time = time;
            procs[idx].tat = procs[idx].completion_time - procs[idx].at;
            procs[idx].wt = procs[idx].tat - procs[idx].bt;
            procs[idx].resp = procs[idx].start_time - procs[idx].at;
            completed++;
            prev_pid = -1; seg_start = -1;
        }
    }
    printf("\n");
    print_average(procs, n);
    printf("\n");
    free(procs);
}

#endif /* PP_H */
