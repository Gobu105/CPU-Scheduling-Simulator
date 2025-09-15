#ifndef GANTT_UTILS_H
#define GANTT_UTILS_H
#include <stdio.h>

/* segments: number of bars in the chart
   label[i] : string for each bar, e.g. "P1", "Idle"
   time[i]  : completion time at the END of each bar
   start    : time when first bar starts (often 0 or first arrival) */
static inline void print_gantt_chart(int segments,
                                     const char *label[],
                                     const int time[],
                                     int start)
{
    printf("\nGantt Chart\n===========\n");

    /* top row: boxes with labels */
    for (int i=0; i<segments; i++) {
        printf("| %-4s ", label[i]);
    }
    printf("|\n");

    /* bottom row: time markers */
    printf("%-5d", start);
    for (int i=0; i<segments; i++) {
        printf("%-7d", time[i]);
    }
    printf("\n");
}
#endif

