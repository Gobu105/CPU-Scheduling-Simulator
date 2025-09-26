#include<stdio.h>
#include "swap.h"
#ifndef FCFS_H
#define FCFS_H

void sortfcfs(int *a, int *b, int *index, int n) {
    int i, j, temp;

    //sorted by arrivial time.
    for (i = 1; i <= n; i++) {
        for (j = i; j <= n; j++) {
            if (a[i] > a[j]) {
                swap(&a[i],&a[j]);
                swap(&b[i],&b[j]);
                swap(&index[i],&index[j]);
            }
        }
    }
}


void fcfs(int *a,int *b,int *index,int n){
     int c[n],w[n],r[n],tat[n];
     int i,j,k;

    //fcfs logic
    sortfcfs(a,b,index,n);

    //Output + Other Data Entry
    printf("\n\nFCFS-First Come First Serve\n=============================\n");
    printf("  \tBT\tAT\tCT\tWT\tRT\tTAT\n");
    for(i=1;i<=n;i++){
                      if(i==1){
                               c[i]=b[i];}
                      else{
                               c[i]=c[i-1]+b[i];}
                      w[i]=c[i]-b[i]-a[i];
                      r[i]=w[i];
                      tat[i]=c[i]-a[i];
                      printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",index[i],b[i],a[i],c[i],w[i],r[i],tat[i]);
    }
}
void fcfsgantt(int *a,int *b,int *index, int n){
        //fcfs logic
        sortfcfs(a,b,index,n);
	int i,j;
        //Gantt Chart
        printf("\n\nGantt Chart\n===========\n");
        for(i=1;i<=n;i++){
                        printf("|P%d",index[i]);
                        for(j=0;j<b[i];j++)
                                         printf(" ");
    }
}

#endif
