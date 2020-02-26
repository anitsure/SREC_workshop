#include <unistd.h>
#include "mm.h"

void init_arrays_matmul()
{
	int j = 0;
	
	printf("init_arrays_matmul::array size: %d \n", ROWSIZE*COLSIZE);

	pA = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);
	pB = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);
	pC = (double*) malloc(sizeof(double) * ROWSIZE*COLSIZE);

	#if ( __OPENMP_CPU__ || __OPENMP_GPU__ )
	  printf("First touch initialization %dx%d \n", ROWSIZE,COLSIZE);
	  // TODO: Add OpenMP pragma for CPU thread parallelization
	  #pragma omp parallel for
	#endif
	for (j=0; j<ROWSIZE*COLSIZE; j++) 
	{
        pA[j] = 2.0;
        pB[j] = 6.0;
        pC[j] = 0.0;
    }
}

void matrix_multiplication()
{
	int i = 0;
	int j = 0;
	int k = 0;
	

	#ifdef __OPENMP_GPU__

	  printf("Inside matrix_multiplication GPU %dx%d \n", ROWSIZE,COLSIZE);
	  int gpuid = 0;
	  // TODO: Map data (matrices) on GPU
	  #pragma omp target data map (to: pA[0:ROWSIZE*COLSIZE],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[0:ROWSIZE*COLSIZE]) device(gpuid)

	  // TODO: Add OpenMP pragma to offload functionality on GPU
	  #pragma omp target device(gpuid)
	  #pragma omp teams distribute parallel for collapse(2) private(i,j,k) 

	#endif

	#ifdef __OPENMP_CPU__
	  printf("Inside matrix_multiplication CPU %dx%d \n", ROWSIZE,COLSIZE);
	  // TODO: Add OpenMP pragma for CPU thread parallelization
	  #pragma omp parallel for collapse(2) private(i,j,k) shared(pA,pB,pC)
	#endif
	for(i=0;i<ROWSIZE;i++)
	{
		for(j=0;j<COLSIZE;j++)
		{
			for(k=0;k<ROWSIZE;k++)
			{
				pC(i,j)+=pA(i,k)*pB(k,j);
			}
		}
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

