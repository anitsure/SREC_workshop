
#ifndef _STREAM_H_
#define _STREAM_H_

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

//#define ARRAY_SIZE 10000000 
#ifndef ROWSIZE
	#define ROWSIZE 25027
#endif

#ifndef COLSIZE
	#define COLSIZE 25027
#endif

#define a(i,j) (a[((i)*COLSIZE) + (j)])
#define b(i,j) (b[((i)*COLSIZE) + (j)])
#define c(i,j) (c[((i)*COLSIZE) + (j)])

#define pA(i,j) (pA[((i)*COLSIZE) + (j)])
#define pB(i,j) (pB[((i)*COLSIZE) + (j)])
#define pC(i,j) (pC[((i)*COLSIZE) + (j)])

#define pBT(i,j) (pBT[((i)*COLSIZE) + (j)])

#define recA(i,j) (recA[((i)*COLSIZE) + (j)])
#define recC(i,j) (recC[((i)*COLSIZE) + (j)])

#define pD(i,j) (pA[((i)*COLSIZE) + (j)])
#define pE(i,j) (pB[((i)*COLSIZE) + (j)])
#define pF(i,j) (pC[((i)*COLSIZE) + (j)])

double scalar; 
int num_teams,
	num_gpu_threads,
	array_size;

double *a, *b, *c;
double *pA, *pB, *pC, *pBT, *recA, *recC;
double *mA, *mB, *mC;

/*
double a[ARRAY_SIZE],
       b[ARRAY_SIZE],
       c[ARRAY_SIZE];

double pA[ARRAY_SIZE],
       pB[ARRAY_SIZE],
       pC[ARRAY_SIZE];
*/

void triad_1loop();

void matrix_multiplication();

void triad_1loop_gpuoffload(int gpuid);
void triad_2loop_gpuoffload(int, int);

void matrix_multiplication_gpuoffload(int gpuid, int, int, double*, double*);
void matrix_multiplication_gpuoffload_split();
void matrix_multiplication_gpuoffload_teams(int);
void matrix_multiplication_gpuoffload_schedule(int);
void matrix_multiplication_gpuoffload_multigpu();
void matrix_multiplication_gpuoffload_Async();
void matrix_multiplication_gpuoffload_UVM(int gpuid);
void matrix_multiplication_multigpuoffload();
void matrix_multiplication_gpuoffload_ats(int gpuid);

void transpose();
//void transpose(double* pBT);
void print_matrix(double *pC);

#endif
