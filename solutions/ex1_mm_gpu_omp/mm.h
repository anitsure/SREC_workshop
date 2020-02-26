
#ifndef _MM_H_
#define _MM_H_

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
#define pB(i,j) (pB[((i)*COLSIZE) + (j)])
#define pC(i,j) (pC[((i)*COLSIZE) + (j)])

double *pA, *pB, *pC;

void matrix_multiplication();

void print_matrix(double *pC);

#endif
