
#include "mm.h"

void matrix_multiplication_partial(int gpuid) 
{
	int i = 0;
	int j = 0;
	int k = 0;

	// get the number of devices (GPUs) on the node.
	int ng = omp_get_num_devices(); //4
	
	// the domain decomposition implementation assumes 4 GPUs on the system. 
	// In case the program executed on 6 GPUs system, setting up number of GPUs to 4.
	if(ng > 4)
	{
		ng = 4;
	}
	
	// calculate number of elements per GPU
	int num_elements = ROWSIZE*COLSIZE/ng;

	// find the starting index of array for respective GPU
	int startInd = gpuid*num_elements;

	// start and end of i-index for square matrix traversal 
	int is = gpuid * (ROWSIZE/ng);
	int ie = is + (ROWSIZE/ng);

	printf("Inside mm_multiply_temp::startInd=%d, num_elements=%d, ng: %d, gpuid: %d \n", startInd,num_elements, ng, gpuid);

	// TODO: Map data (matrices) on GPU
	#pragma omp target data map (to: pA[startInd:num_elements],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[startInd:num_elements]) device(gpuid)
	#pragma omp target map (to: pA[startInd:num_elements],pB[0:ROWSIZE*COLSIZE]) map (tofrom: pC[startInd:num_elements]) device(gpuid)
	
	// TODO: Add OpenMP pragma to offload functionality on GPU
	#pragma omp teams distribute parallel for collapse(2) private(i,j,k) 
	for(i=is;i<ie;i++)
	{
		for(j=0;j<COLSIZE;j++)
		{
			for(k=0; k<COLSIZE; k++)
			{
				pC(i,j)+=pA(i,k)*pB(k,j);
			}
		}
	}
	
}

void matrix_multiplication_multigpuoffload()
{

	//distribute work on multiple GPUs
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			matrix_multiplication_partial(0);
		}
		#pragma omp section
		{
			matrix_multiplication_partial(1);
		}
	
		#pragma omp section
		{
			matrix_multiplication_partial(2);
		}
		#pragma omp section
		{
			matrix_multiplication_partial(3);
		}
	}
}
