#include<stdio.h>
#include "swap.h"
#ifndef SJF_H
#define SJF_H

void sjfsort(int *a, int *b, int *index, int n) {
    int i, j, clock=0;

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

    //sorted by burst time.
    for(i=1;i<=n;i++){
                      clock+=b[i];
                      int pos=i+1;
                      for(j=i+1;j<=n;j++){
                                          if(a[j] <= clock && b[j] < b[pos])
                                                         pos=j;
                      }
                      if (pos!=i+1){
                                       swap(&a[i+1],&a[pos]);
                                       swap(&b[i+1],&b[pos]);
                                       swap(&index[i+1],&index[pos]);
                      }
    }
}


void sjf(int *a,int *b,int *index,int n){
     int c[n],w[n],r[n],tat[n];
     int i,j,k;

    //fcfs logic
    sjfsort(a,b,index,n);
    //Output + Other Data Entry
    printf("\n\nSJF-Shortest Job First\n=============================\n");
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

void sjfgantt(int *a,int *b,int *index,int n){
        //fcfs logic
        sjfsort(a,b,index,n);
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
