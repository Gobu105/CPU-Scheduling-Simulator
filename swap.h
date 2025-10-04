
#include<stdio.h>
#ifndef SWAP_H
#define SWAP_H

void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=*a;
}

#endif