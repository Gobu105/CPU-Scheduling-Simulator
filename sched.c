/*
Project: Scheduling Simulator in C
Files included in this single document (split into separate files when saving):
 - utils.h
 - fcfs.h
 - sjf.h
 - srt.h
 - pp.h    (preemptive priority)
 - pnp.h   (non-preemptive priority)
 - rr.h
 - main.c

Each scheduling header implements a function that accepts an array of Process and number of processes
and prints a Gantt chart and a table with AT, BT, (Priority if applicable), WT, TAT, RT.

Compile: gcc main.c -o sched && ./sched
*/

/* ========================= main.c ========================= */
#include "utils.h"
#include "fcfs.h"
#include "sjf.h"
#include "srt.h"
#include "pp.h"
#include "pnp.h"
#include "rr.h"

int main() {
  /* Example: you can modify this to take user input or read from a file */
  char cmd[64], alg[16];
  int n = 0,quantum=2;
  Process *procs;

  printf("Scheduling Shell. Commands:\n");
  printf("  scheduling   - enter processes\n");
  printf("  gantt [alg]  - show Gantt chart for all or specific algorithm\n");
  printf("  table [alg]  - show table for all or specific algorithm\n");
  printf("  average      - show avg WT and TAT of all algorithms (RT N/A)\n");
  printf("  quantum x    - set RR time quantum\n");
  printf("  quit         - exit\n");

  while (1) {
    printf("\n> ");
    if (scanf("%63s", cmd) != 1)
      break;

    // flush leftover input
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (!strcmp(cmd, "quit"))
      break;

    else if (!strcmp(cmd, "scheduling")) {
      printf("Enter number of processes: ");
      scanf("%d", &n);
      procs =(Process*) malloc(sizeof(Process) * n);

      for (int i = 0; i < n; ++i) {
        procs[i].pid = i + 1;
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &procs[i].at);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &procs[i].bt);
        procs[i].priority = 0;  /* default */
      }

      int need_prio = 0;
      printf("Do you want to enter priorities for PP/PNP? (1/0): ");
      scanf("%d", &need_prio);

      if (need_prio) {
        for (int i = 0; i < n; ++i) {
          printf("Priority for P%d (lower is higher priority): ", procs[i].pid);
          scanf("%d", &procs[i].priority);
        }
      }
      printf("Enter time quantum for RR (suggested 2): ");
      scanf("%d", &quantum);
      
      while ((c = getchar()) != '\n' && c != EOF);  // flush newline
      printf("Processes entered successfully.\n");
    }

    else if (cmd != NULL) {
      if (n != 0) {
        if (!strcmp(cmd, "quantum")) {
          printf("Enter RR time quantum: ");
          if (scanf("%d", &quantum) != 1 || quantum <= 0) {
            printf("Invalid quantum.\n");
          } else {
            printf("RR quantum set to %d\n", quantum);
          }
          while ((c = getchar()) != '\n' && c != EOF);
        }

        else if (!strcmp(cmd, "gantt") || !strcmp(cmd, "table")) {
          int show_gantt = !strcmp(cmd, "gantt");
          int show_table = !strcmp(cmd, "table");

          if (scanf("%15s", alg) != 1)
            strcpy(alg, "all");

          while ((c = getchar()) != '\n' && c != EOF);

          if (show_gantt) {
            if (!strcmp(alg, "fcfs") || !strcmp(alg, "all"))
              fcfsgantt(procs, n);
            if (!strcmp(alg, "sjf") || !strcmp(alg, "all"))
              sjfgantt(procs, n);
            if (!strcmp(alg, "srt") || !strcmp(alg, "all"))
              srtgantt(procs, n);
            if (!strcmp(alg, "pnp") || !strcmp(alg, "all"))
              pnpgantt(procs, n);
            if (!strcmp(alg, "pp") || !strcmp(alg, "all"))
              ppgantt(procs, n);
	    if (!strcmp(alg, "rr") || !strcmp(alg, "all"))
              rrgantt(procs, n,quantum);
          }

          if (show_table) {
            if (!strcmp(alg, "fcfs") || !strcmp(alg, "all"))
              fcfs(procs, n);
            if (!strcmp(alg, "sjf") || !strcmp(alg, "all"))
              sjf(procs, n);
            if (!strcmp(alg, "srt") || !strcmp(alg, "all"))
              srt(procs, n);
            if (!strcmp(alg, "pnp") || !strcmp(alg, "all"))
              pnp(procs, n);
            if (!strcmp(alg, "pp") || !strcmp(alg, "all"))
              pp(procs, n);
            if (!strcmp(alg, "rr") || !strcmp(alg, "all"))
              rr(procs, n,quantum);
          }
        }

        else if (!strcmp(cmd, "average")) {
	    if (scanf("%15s", alg) != 1)
             strcpy(alg, "all");
            while ((c = getchar()) != '\n' && c != EOF);

            if (!strcmp(alg, "fcfs") || !strcmp(alg, "all"))
              fcfsaverage(procs, n);
	    if (!strcmp(alg, "sjf") || !strcmp(alg, "all"))
              sjfaverage(procs, n);
            if (!strcmp(alg, "srt") || !strcmp(alg, "all"))
              srtaverage(procs, n);
            if (!strcmp(alg, "pnp") || !strcmp(alg, "all"))
              pnpaverage(procs, n);
            if (!strcmp(alg, "pp") || !strcmp(alg, "all"))
              ppaverage(procs, n);
            if (!strcmp(alg, "rr") || !strcmp(alg, "all"))
              rraverage(procs, n,quantum);
        }
      } else {
        printf("Process are not entered!!");
      }
    }

    else {
      printf("Unknown command.\n");
    }
  }

  free(procs);
  return 0;
}
