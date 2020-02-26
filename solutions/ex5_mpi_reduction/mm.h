
#ifndef _STREAM_H_
#define _STREAM_H_

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#ifndef ROWSIZE
	#define ROWSIZE 25027
#endif

#ifndef COLSIZE
	#define COLSIZE 25027
#endif

#define pA(i,j) (pA[((i)*COLSIZE) + (j)])
#define recA(i,j) (recA[((i)*COLSIZE) + (j)])

double *pA, *recA;

void print_matrix(double *pC);

#endif
