#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fcfs.h"
#include "sjf.h"
#include "srt.h"
#include "pp.h"
//#include "pnp.h"
#include "rr.h"

#define MAX_PROCESSES 50

int main() {
    char cmd[64], alg[16];
    int arrival[MAX_PROCESSES], burst[MAX_PROCESSES], index[MAX_PROCESSES];
    int priority[MAX_PROCESSES];
    int n = 0;
    int rr_tq = 0;

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

        // flush leftover input
        int c; while((c=getchar())!='\n' && c!=EOF);

        if (!strcmp(cmd,"quit")) break;

        else if (!strcmp(cmd,"scheduling")) {
            printf("Enter number of processes: ");
            if(scanf("%d", &n)!=1 || n<=0 || n>MAX_PROCESSES){
                printf("Invalid number of processes.\n");
                while((c=getchar())!='\n' && c!=EOF);
                continue;
            }
            for(int i=1;i<=n;i++){
                printf("Process %d -> Arrival, Burst: ", i);
                if(scanf("%d %d", &arrival[i], &burst[i])!=2 || arrival[i]<0 || burst[i]<=0){
                    printf("Invalid input, try again.\n"); i--; 
                    while((c=getchar())!='\n' && c!=EOF);
                    continue;
                }
                index[i]=i;
            }
            while((c=getchar())!='\n' && c!=EOF); // flush newline
            printf("Processes entered successfully.\n");
        }
	else if(cmd!=NULL){
		if(n!=0){
        if (!strcmp(cmd,"quantum")) {
            printf("Enter RR time quantum: ");
            if(scanf("%d", &rr_tq)!=1 || rr_tq<=0){
                printf("Invalid quantum.\n");
            } else {
                printf("RR quantum set to %d\n", rr_tq);
            }
            while((c=getchar())!='\n' && c!=EOF);
        }

        else if (!strcmp(cmd,"gantt") || !strcmp(cmd,"table")) {
            int show_gantt = !strcmp(cmd,"gantt");
            int show_table = !strcmp(cmd,"table");

            if(scanf("%15s", alg)!=1) strcpy(alg,"all");
            while((c=getchar())!='\n' && c!=EOF); // flush newline

            // Call PP/PNP priority input if needed
            if (!strcmp(alg,"pp") || !strcmp(alg,"pnp") || !strcmp(alg,"all")) input(priority,n);
            // Call RR input if quantum not set
            if ((!strcmp(alg,"rr") || !strcmp(alg,"all")) && rr_tq<=0) rrinput(&rr_tq);

            if(show_gantt){
                if(!strcmp(alg,"fcfs")||!strcmp(alg,"all")) fcfsgantt(arrival, burst, index, n);
                if(!strcmp(alg,"sjf")||!strcmp(alg,"all")) sjfgantt(arrival, burst, index, n);
                if(!strcmp(alg,"srt")||!strcmp(alg,"all")) srtgantt(arrival, burst, index, n);
                if(!strcmp(alg,"pp")||!strcmp(alg,"all")) ppgantt(burst, priority, index, n);
                if(!strcmp(alg,"rr")||!strcmp(alg,"all")) rrgantt(arrival, burst, index, n, rr_tq);
            }

            if(show_table){
                if(!strcmp(alg,"fcfs")||!strcmp(alg,"all")) fcfs(arrival, burst, index, n);
                if(!strcmp(alg,"sjf")||!strcmp(alg,"all")) sjf(arrival, burst, index, n);
                if(!strcmp(alg,"srt")||!strcmp(alg,"all")) srt(arrival, burst, index, n);
                if(!strcmp(alg,"pp")||!strcmp(alg,"all")) pp(burst, priority, index, n);
                //if(!strcmp(alg,"pnp")||!strcmp(alg,"all")) pnp_table_wrapper(arrival, burst, priority, index, n);
                if(!strcmp(alg,"rr")||!strcmp(alg,"all")) rr(arrival, burst, index, n, rr_tq);
            }
        }
/*
        else if(!strcmp(cmd,"average")) {
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
*/
	}
	else{
		printf("Process are not entered!!");
	}
    }
        else printf("Unknown command.\n");
    }

    return 0;
}

