#include "utils.h"
#include "fcfs.h"
#include "sjf.h"
#include "srt.h"
#include "pp.h"
#include "pnp.h"
#include "rr.h"

int main() {
    char cmd[64], alg[16];
    int n = 0, quantum = 2;
    Process *procs = NULL;

    printf("Scheduling Shell. Commands:\n");
    printf("  scheduling   - enter processes\n");
    printf("  gantt [alg]  - show Gantt chart for all or specific algorithm\n");
    printf("  table [alg]  - show table for all or specific algorithm\n");
    printf("  average      - show avg WT and TAT of all algorithms\n");
    printf("  quantum x    - set RR time quantum\n");
    printf("  quit         - exit\n");

    while (1) {
        printf("\n> ");
        if (scanf("%63s", cmd) != 1)
            break;

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (!strcmp(cmd, "quit"))
            break;

        else if (!strcmp(cmd, "scheduling")) {
            printf("Enter number of processes: ");
            if (scanf("%d", &n) != 1 || n <= 0) {   // ✅ Validation
                printf("❌ Invalid number of processes. Try again.\n");
                while ((c = getchar()) != '\n' && c != EOF);
                continue;
            }

            free(procs); // free old memory if re-running scheduling
            procs = (Process*) malloc(sizeof(Process) * n);
            if (!procs) {   // ✅ Validation
                fprintf(stderr, "❌ Memory allocation failed.\n");
                exit(1);
            }

            for (int i = 0; i < n; ++i) {
                procs[i].pid = i + 1;

                // Arrival Time
                do {
                    printf("Process %d - Arrival Time: ", i + 1);
                    if (scanf("%d", &procs[i].at) != 1 || procs[i].at < 0) {
                        printf("❌ Invalid input! Arrival time must be >= 0.\n");
                        while ((c = getchar()) != '\n' && c != EOF);
                        continue;
                    }
                    break;
                } while (1);

                // Burst Time
                do {
                    printf("Process %d - Burst Time: ", i + 1);
                    if (scanf("%d", &procs[i].bt) != 1 || procs[i].bt <= 0) {
                        printf("❌ Invalid input! Burst time must be > 0.\n");
                        while ((c = getchar()) != '\n' && c != EOF);
                        continue;
                    }
                    break;
                } while (1);

                procs[i].priority = 0;
                procs[i].rt_time = procs[i].bt;
            }

            int need_prio = 0;
            printf("Do you want to enter priorities for PP/PNP? (1/0): ");
            if (scanf("%d", &need_prio) != 1 || (need_prio != 0 && need_prio != 1)) { // ✅ Validation
                printf("Invalid input, skipping priority entry.\n");
                need_prio = 0;
            }

            if (need_prio) {
                for (int i = 0; i < n; ++i) {
                    do {
                        printf("Priority for P%d (lower = higher): ", procs[i].pid);
                        if (scanf("%d", &procs[i].priority) != 1 || procs[i].priority < 0) {
                            printf("❌ Invalid priority! Must be >= 0.\n");
                            while ((c = getchar()) != '\n' && c != EOF);
                            continue;
                        }
                        break;
                    } while (1);
                }
            }

            do {
                printf("Enter time quantum for RR (suggested 2): ");
                if (scanf("%d", &quantum) != 1 || quantum <= 0) {  // ✅ Validation
                    printf("❌ Invalid quantum! Must be > 0.\n");
                    while ((c = getchar()) != '\n' && c != EOF);
                    continue;
                }
                break;
            } while (1);

            while ((c = getchar()) != '\n' && c != EOF);
            printf("✅ Processes entered successfully.\n");
        }

        else if (!strcmp(cmd, "quantum")) {
            printf("Enter RR time quantum: ");
            if (scanf("%d", &quantum) != 1 || quantum <= 0) {  // ✅ Validation
                printf("❌ Invalid quantum value.\n");
            } else {
                printf("RR quantum set to %d\n", quantum);
            }
            while ((c = getchar()) != '\n' && c != EOF);
        }

        else if (!strcmp(cmd, "gantt") || !strcmp(cmd, "table")) {
            int show_gantt = !strcmp(cmd, "gantt");
            int show_table = !strcmp(cmd, "table");

            if (n == 0 || !procs) {
                printf("❌ No processes entered yet. Use 'scheduling' first.\n");
                continue;
            }
            printf("Enter algorithm name (all/fcfs/sjf/srt/pp/pnp/rr): ");
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
                    rrgantt(procs, n, quantum);
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
                    rr(procs, n, quantum);
            }
        }

        else if (!strcmp(cmd, "average")) {
            if (n == 0 || !procs) {
                printf("❌ No processes entered yet. Use 'scheduling' first.\n");
                continue;
            }
            printf("Enter algorithm name (all/fcfs/sjf/srt/pp/pnp/rr): ");
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
                rraverage(procs, n, quantum);
        }

        else {
            printf("❌ Unknown command. Try again.\n");
        }
    }

    free(procs);
    return 0;
}
