#include <unistd.h>
#include "mm.h"

void init_arrays_matmul_mpi(int np, int rank)
{
	int j = 0;
	
	recA = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);

	if(rank == 0)
	{
		printf("init_arrays_matmul::array size: %d \n", ROWSIZE*COLSIZE);
		pA = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);
		#pragma omp parallel for
		for (j=0; j<ROWSIZE*COLSIZE; j++) 
		{
       			pA[j] = 2.0;
    		}
	}

	for (int i=0; i< ROWSIZE/np * COLSIZE; i++)
	{
		recA[i] = 0.0;
	}
}

void print_matrix(double *pA)
{
	int i = 0;
	int j = 0;
	
	printf("######################### 2D printing ########################################### \n");

	for(i=0; i<ROWSIZE; i++)
	{
		for(j=0; j<COLSIZE; j++)
		{
			printf("%f ", pA(i,j));
		}
		printf("\n");
	}
	
	printf("######################### 1D printing ########################################### \n");

	for(i=0; i<ROWSIZE*COLSIZE; i++)
	{
		printf("%f ", pA[i]);
	}
	printf("\n");
}

