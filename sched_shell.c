#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fcfs.h"
#include "sjf.h"
#include "srt.h"
#include "pnp.h"
#include "pp.h"
#include "rr.h"

#define MAX 50

typedef struct {
    int pid;
    int arrival;
    int burst;
    int priority;
} BaseProc;

static BaseProc base[MAX];
static int n = 0;
static int quantum = 2; // default RR quantum

typedef struct {
    double avg_wt;
    double avg_tat;
} Averages;   // RT omitted for now – the headers do not provide it

//------------------------------------------------------------
void read_processes(void)
{
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        base[i].pid = i + 1;
        printf("Process %d arrival and burst: ", base[i].pid);
        scanf("%d %d", &base[i].arrival, &base[i].burst);
        base[i].priority = 1; // default priority
    }
}

//---- Each wrapper runs the algorithm & returns averages ----
Averages run_fcfs(int show_gantt, int show_table) {
    FCFSProcess p[MAX];
    for (int i=0;i<n;i++){
        p[i].pid=base[i].pid; p[i].arrival=base[i].arrival; p[i].burst=base[i].burst;
    }
    calculateFCFS(p,n);
    if (show_gantt || show_table) printf("\n[FCFS]\n");
    if (show_table) displayFCFSTable(p,n);

    double wt=0,tat=0;
    for (int i=0;i<n;i++){ wt+=p[i].waiting; tat+=p[i].turnaround; }
    return (Averages){wt/n, tat/n};
}

Averages run_sjf(int show_gantt, int show_table) {
    SJFProcess p[MAX];
    for (int i=0;i<n;i++){
        p[i].pid=base[i].pid; p[i].arrival=base[i].arrival; p[i].burst=base[i].burst;
    }
    calculateSJF(p,n);
    if (show_gantt || show_table) printf("\n[SJF]\n");
    if (show_table) displaySJFTable(p,n);

    double wt=0,tat=0;
    for (int i=0;i<n;i++){ wt+=p[i].waiting; tat+=p[i].turnaround; }
    return (Averages){wt/n, tat/n};
}

Averages run_srt(int show_gantt, int show_table) {
    SRTProcess p[MAX];
    for (int i=0;i<n;i++){
        p[i].pid=base[i].pid; p[i].arrival=base[i].arrival; p[i].burst=base[i].burst;
    }
    calculateSRT(p,n);
    if (show_gantt || show_table) printf("\n[SRT]\n");
    if (show_table) displaySRTTable(p,n);

    double wt=0,tat=0;
    for (int i=0;i<n;i++){ wt+=p[i].waiting; tat+=p[i].turnaround; }
    return (Averages){wt/n, tat/n};
}

Averages run_pnp(int show_gantt, int show_table) {
    PNPProcess p[MAX];
    for (int i=0;i<n;i++){
        p[i].pid=base[i].pid; p[i].arrival=base[i].arrival; p[i].burst=base[i].burst;
        p[i].priority = base[i].priority;
    }
    calculatePNP(p,n);
    if (show_gantt || show_table) printf("\n[PNP]\n");
    if (show_table) displayPNPTable(p,n);

    double wt=0,tat=0;
    for (int i=0;i<n;i++){ wt+=p[i].waiting; tat+=p[i].turnaround; }
    return (Averages){wt/n, tat/n};
}

Averages run_pp(int show_gantt, int show_table) {
    PPProcess p[MAX];
    for (int i=0;i<n;i++){
        p[i].pid=base[i].pid; p[i].arrival=base[i].arrival; p[i].burst=base[i].burst;
        p[i].priority = base[i].priority;
    }
    calculatePP(p,n);
    if (show_gantt || show_table) printf("\n[PP]\n");
    if (show_table) displayPPTable(p,n);

    double wt=0,tat=0;
    for (int i=0;i<n;i++){ wt+=p[i].waiting; tat+=p[i].turnaround; }
    return (Averages){wt/n, tat/n};
}

Averages run_rr(int show_gantt, int show_table) {
    RRProcess p[MAX];
    for (int i=0;i<n;i++){
        p[i].pid=base[i].pid; p[i].arrival=base[i].arrival; p[i].burst=base[i].burst;
    }
    calculateRR(p,n,quantum);
    if (show_gantt || show_table) printf("\n[RR]\n");
    if (show_table) displayRRTable(p,n);

    double wt=0,tat=0;
    for (int i=0;i<n;i++){ wt+=p[i].waiting; tat+=p[i].turnaround; }
    return (Averages){wt/n, tat/n};
}

//------------------------------------------------------------
int main(void)
{
    char cmd[64];
    printf("Scheduling Shell. Commands:\n");
    printf("  scheduling   - enter processes\n");
    printf("  gantt [alg]  - show Gantt chart for all or specific algorithm\n");
    printf("  table [alg]  - show table for all or specific algorithm\n");
    printf("  average      - show avg WT and TAT of all algorithms (RT N/A)\n");
    printf("  quantum x    - set RR time quantum\n");
    printf("  quit         - exit\n");

    while (1) {
        printf("\n> ");
        if (scanf("%63s", cmd) != 1) break;

        if (!strcmp(cmd,"quit")) break;

        else if (!strcmp(cmd,"scheduling")) {
            read_processes();
        }
        else if (!strcmp(cmd,"quantum")) {
            scanf("%d", &quantum);
            printf("Quantum set to %d\n", quantum);
        }
        else if (!strcmp(cmd,"gantt") || !strcmp(cmd,"table")) {
            char alg[16];
            int hasAlg = scanf("%15s", alg);
            if (hasAlg != 1) strcpy(alg,"all");

            int show_gantt = !strcmp(cmd,"gantt");
            int show_table = !strcmp(cmd,"table");

            #define RUN(NAME,FUNC) \
                if(!strcmp(alg,"all")||!strcmp(alg,NAME)){ FUNC(show_gantt, show_table); }

            RUN("fcfs", run_fcfs);
            RUN("sjf",  run_sjf);
            RUN("srt",  run_srt);
            RUN("pnp",  run_pnp);
            RUN("pp",   run_pp);
            RUN("rr",   run_rr);
        }
        else if (!strcmp(cmd,"average")) {
            printf("\nAlgorithm | Avg WT | Avg TAT | Avg RT (N/A)\n");
            printf("-------------------------------------------\n");
            Averages a;

            a = run_fcfs(0,0);
            printf("FCFS      | %.2f  | %.2f   |  N/A\n",a.avg_wt,a.avg_tat);

            a = run_sjf(0,0);
            printf("SJF       | %.2f  | %.2f   |  N/A\n",a.avg_wt,a.avg_tat);

            a = run_srt(0,0);
            printf("SRT       | %.2f  | %.2f   |  N/A\n",a.avg_wt,a.avg_tat);

            a = run_pnp(0,0);
            printf("PNP       | %.2f  | %.2f   |  N/A\n",a.avg_wt,a.avg_tat);

            a = run_pp(0,0);
            printf("PP        | %.2f  | %.2f   |  N/A\n",a.avg_wt,a.avg_tat);

            a = run_rr(0,0);
            printf("RR        | %.2f  | %.2f   |  N/A\n",a.avg_wt,a.avg_tat);
        }
        else {
            printf("Unknown command.\n");
        }
    }
    return 0;
}
