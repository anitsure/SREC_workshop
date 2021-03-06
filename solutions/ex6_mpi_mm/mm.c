#include <unistd.h>
#include "mm.h"

void matrix_multiplication(int np, int pid, double *recA, double *recC)
{
	int i = 0;
	int j = 0;
	int k = 0;
	
	printf("Inside MPI matrix_multiplication %dx%d : %d \n", ROWSIZE/np,COLSIZE, pid);
	#pragma omp parallel for collapse(2) private(i,j,k) shared(recA,pB,recC)
	for(i=0;i<ROWSIZE/np;i++)
	{
		for(j=0;j<COLSIZE;j++)
		{
			for(k=0;k<COLSIZE;k++)
			{
				recC(i,j)+=recA(i,k)*pB(k,j);

//				printf("recC(%d,%d) = recA(%d,%d)*pB(%d,%d) \n",i,j, i, k, k, j);
//				printf("proc (%d) : recA(%d,%d): %f \n",pid, i,k, recA(i,k) );
			}
			//printf("pC: %f = pA: * pB: \n",pC(i,j)); 
		}
	}	
}


void init_arrays_matmul_mpi(int np, int pid)
{
	int j = 0;
	
	printf("init_arrays_matmul::array size: %d \n", ROWSIZE*COLSIZE);

	pB = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);

	recA = (double*) malloc(sizeof(double) * ROWSIZE/np * COLSIZE);
    recC = (double*) malloc(sizeof(double) * ROWSIZE/np * COLSIZE);

	if(pid == 0)
	{
		pA = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);
		pC = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);

		#pragma omp parallel for
		for (j=0; j<ROWSIZE*COLSIZE; j++) 
		{
       		pA[j] = 2.0;
	        pB[j] = 6.0;
    	    pC[j] = 0.0;
    	}
	}
	
	printf (" process %d create rec buffer \n " , pid ) ;
	
	for (int i=0; i< ROWSIZE/np * COLSIZE; i++)
	{
		recA[i] = 0;
		recC[i] = 0;
	}
}

void print_matrix(double *pC)
{
	int i = 0;
	int j = 0;
	
	printf("######################### 2D printing ########################################### \n");

	for(i=0; i<ROWSIZE; i++)
	{
		for(j=0; j<COLSIZE; j++)
		{
			printf("%f ", pC(i,j));
		}
		printf("\n");
	}
	
	printf("######################### 1D printing ########################################### \n");

	for(i=0; i<ROWSIZE*COLSIZE; i++)
	{
		printf("%f ", pC[i]);
	}
	printf("\n");
}

