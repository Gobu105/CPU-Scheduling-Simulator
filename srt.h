#include<stdio.h>
#include "swap.h"
#ifndef SRT_H
#define SRT_H

void srt(int *a, int *b, int *index, int n){
    int rem[n+1], c[n+1], w[n+1], r[n+1], tat[n+1];
    int done[n+1];  // mark completion
    int i;
    for(i=1;i<=n;i++){
        rem[i] = b[i];      // remaining burst
        done[i] = 0;
        r[i] = -1;          // response time not yet set
    }

    int time = 0, completed = 0;
    while(completed < n){
        int min_idx = -1;
        int min_rem = 1e9;

        // find process with smallest remaining time among arrived ones
        for(i=1;i<=n;i++){
            if(!done[i] && a[i] <= time && rem[i] < min_rem && rem[i] > 0){
                min_rem = rem[i];
                min_idx = i;
            }
        }

        if(min_idx == -1){
            // no process has arrived yet, jump time
            time++;
            continue;
        }

        if(r[min_idx] == -1)
            r[min_idx] = time - a[min_idx]; // response time = first start - arrival

        // run for 1 unit
        rem[min_idx]--;
        time++;

        if(rem[min_idx] == 0){
            done[min_idx] = 1;
            completed++;
            c[min_idx] = time; // completion time
            tat[min_idx] = c[min_idx] - a[min_idx];
            w[min_idx]   = tat[min_idx] - b[min_idx];
        }
    }

    printf("\n\nSRTF-Shortest Remaining Time First\n====================================\n");
    printf("  \tBT\tAT\tCT\tWT\tRT\tTAT\n");
    for(i=1;i<=n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               index[i], b[i], a[i], c[i], w[i], r[i], tat[i]);
    }
}

void srtgantt(int *a, int *b, int *index, int n){
    int rem[n+1], done[n+1], i;
    for(i=1;i<=n;i++){
        rem[i] = b[i];
        done[i] = 0;
    }

    int time = 0, completed = 0;
    printf("\n\nGantt Chart\n===========\n");
    printf("|");
    while(completed < n){
        int min_idx = -1;
        int min_rem = 1e9;
        for(i=1;i<=n;i++){
            if(!done[i] && a[i] <= time && rem[i] < min_rem && rem[i] > 0){
                min_rem = rem[i];
                min_idx = i;
            }
        }

        if(min_idx == -1){
            time++;
            continue;
        }

        printf("P%d", index[min_idx]);
        rem[min_idx]--;
        time++;

        if(rem[min_idx] == 0){
            done[min_idx] = 1;
            completed++;
        }
    }
    printf("|\n");
}

#endif
