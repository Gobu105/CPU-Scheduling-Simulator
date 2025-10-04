
/* ========================= rr.h (Round Robin) ========================= */
#ifndef RR_H
#define RR_H
#include "utils.h"

/* quantum: time quantum */
void rr(Process input[], int n, int quantum) {
    print_header("RR (Round Robin)");
    Process *procs = copy_procs(input, n);
    for (int i = 0; i < n; ++i) { procs[i].rt_time = procs[i].bt; procs[i].start_time = -1; }
    int time = 0; int completed = 0;
    int queue[1000]; int front = 0, rear = 0; int in_queue[1000]; memset(in_queue,0,sizeof(in_queue));

    /* enqueue processes that arrive at time 0 */
    for (int i = 0; i < n; ++i) if (procs[i].at == 0) { queue[rear++] = i; in_queue[i]=1; }
    int last = -1, seg_start=-1;
    while (completed < n) {
        if (front == rear) {
            /* no process ready -> advance time to next arrival */
            int tmin = INT_MAX; int idx = -1;
            for (int i = 0; i < n; ++i) if (!in_queue[i] && procs[i].rt_time>0) { if (procs[i].at < tmin) { tmin = procs[i].at; idx = i; } }
            if (idx == -1) break;
            time = procs[idx].at;
            /* enqueue all that arrive now */
            for (int i = 0; i < n; ++i) if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time>0) { queue[rear++] = i; in_queue[i]=1; }
            continue;
        }
        int cur = queue[front++];
        /* enqueue arrivals that have come while waiting? We'll add them after executing slice */
        if (procs[cur].start_time == -1) procs[cur].start_time = time;
        /* Gantt segment */
        if (last != procs[cur].pid) { if (last != -1) last = procs[cur].pid; seg_start = time; }
        int slice = (procs[cur].rt_time < quantum) ? procs[cur].rt_time : quantum;
        procs[cur].rt_time -= slice;
        time += slice;
        /* enqueue newly arrived processes at this time */
        for (int i = 0; i < n; ++i) if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time>0) { queue[rear++] = i; in_queue[i]=1; }
        if (procs[cur].rt_time > 0) {
            queue[rear++] = cur; /* requeue */
        } else {
            procs[cur].completion_time = time;
            procs[cur].tat = procs[cur].completion_time - procs[cur].at;
            procs[cur].wt = procs[cur].tat - procs[cur].bt;
            procs[cur].resp = procs[cur].start_time - procs[cur].at;
            completed++;
            /* mark as finished */
        }
    }
    printf("\n");
    print_table(procs, n, 0);
    free(procs);
}

void rrgantt(Process input[], int n, int quantum){
    print_header("RR (Round Robin)");
    Process *procs = copy_procs(input, n);
    for (int i = 0; i < n; ++i) { procs[i].rt_time = procs[i].bt; procs[i].start_time = -1; }
    int time = 0; int completed = 0;
    int queue[1000]; int front = 0, rear = 0; int in_queue[1000]; memset(in_queue,0,sizeof(in_queue));

    /* enqueue processes that arrive at time 0 */
    for (int i = 0; i < n; ++i) if (procs[i].at == 0) { queue[rear++] = i; in_queue[i]=1; }
    printf("Gantt Chart:\n");
    int last = -1, seg_start=-1;
    while (completed < n) {
        if (front == rear) {
            /* no process ready -> advance time to next arrival */
            int tmin = INT_MAX; int idx = -1;
            for (int i = 0; i < n; ++i) if (!in_queue[i] && procs[i].rt_time>0) { if (procs[i].at < tmin) { tmin = procs[i].at; idx = i; } }
            if (idx == -1) break;
            time = procs[idx].at;
            /* enqueue all that arrive now */
            for (int i = 0; i < n; ++i) if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time>0) { queue[rear++] = i; in_queue[i]=1; }
            continue;
        }
        int cur = queue[front++];
        /* enqueue arrivals that have come while waiting? We'll add them after executing slice */
        if (procs[cur].start_time == -1) procs[cur].start_time = time;
        /* Gantt segment */
        if (last != procs[cur].pid) { if (last != -1) print_gantt_pair(last, seg_start, time); last = procs[cur].pid; seg_start = time; }
        int slice = (procs[cur].rt_time < quantum) ? procs[cur].rt_time : quantum;
        procs[cur].rt_time -= slice;
        time += slice;
        /* enqueue newly arrived processes at this time */
        for (int i = 0; i < n; ++i) if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time>0) { queue[rear++] = i; in_queue[i]=1; }
        if (procs[cur].rt_time > 0) {
            queue[rear++] = cur; /* requeue */
        } else {
            procs[cur].completion_time = time;
            procs[cur].tat = procs[cur].completion_time - procs[cur].at;
            procs[cur].wt = procs[cur].tat - procs[cur].bt;
            procs[cur].resp = procs[cur].start_time - procs[cur].at;
            completed++;
            /* mark as finished */
        }
    }
    if (last != -1) print_gantt_pair(last, seg_start, time);
    printf("|\n");
    free(procs);
}

void rraverage(Process input[], int n, int quantum){
    print_header("RR (Round Robin)");
    Process *procs = copy_procs(input, n);
    for (int i = 0; i < n; ++i) { procs[i].rt_time = procs[i].bt; procs[i].start_time = -1; }
    int time = 0; int completed = 0;
    int queue[1000]; int front = 0, rear = 0; int in_queue[1000]; memset(in_queue,0,sizeof(in_queue));

    /* enqueue processes that arrive at time 0 */
    for (int i = 0; i < n; ++i) if (procs[i].at == 0) { queue[rear++] = i; in_queue[i]=1;}
    int last = -1, seg_start=-1;
    while (completed < n) {
        if (front == rear) {
            /* no process ready -> advance time to next arrival */
            int tmin = INT_MAX; int idx = -1;
            for (int i = 0; i < n; ++i) if (!in_queue[i] && procs[i].rt_time>0) { if (procs[i].at < tmin) { tmin = procs[i].at; idx = i; } }
            if (idx == -1) break;
            time = procs[idx].at;
            /* enqueue all that arrive now */
            for (int i = 0; i < n; ++i) if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time>0) { queue[rear++] = i; in_queue[i]=1; }
            continue;
        }
        int cur = queue[front++];
        /* enqueue arrivals that have come while waiting? We'll add them after executing slice */
        if (procs[cur].start_time == -1) procs[cur].start_time = time;
        /* Gantt segment */
        if (last != procs[cur].pid){ if (last != -1) last = procs[cur].pid; seg_start = time; }
        int slice = (procs[cur].rt_time < quantum) ? procs[cur].rt_time : quantum;
        procs[cur].rt_time -= slice;
        time += slice;
        /* enqueue newly arrived processes at this time */
        for (int i = 0; i < n; ++i) if (!in_queue[i] && procs[i].at <= time && procs[i].rt_time>0) { queue[rear++] = i; in_queue[i]=1; }
        if (procs[cur].rt_time > 0) {
            queue[rear++] = cur; /* requeue */
        } else {
            procs[cur].completion_time = time;
            procs[cur].tat = procs[cur].completion_time - procs[cur].at;
            procs[cur].wt = procs[cur].tat - procs[cur].bt;
            procs[cur].resp = procs[cur].start_time - procs[cur].at;
            completed++;
            /* mark as finished */
        }
    }
    printf("\n");
    print_average(procs, n);
    printf("\n");
    free(procs);
}

#endif /* RR_H */
