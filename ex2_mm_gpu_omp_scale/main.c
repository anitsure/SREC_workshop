
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<math.h>

#include <sys/time.h>

#include "mm.h"

void init_arrays_matmul();

/* A gettimeofday routine to give access to the wall
 *    clock timer on most UNIX-like systems.  */

double mysecond()
{
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

int validate_input()
{
	if ((ROWSIZE) != (COLSIZE))
	{
		printf("Incorrect matrix dimensions. Cannot multiply Matrix A and Matrix B ! \n");
		return 1;
	}
	if ((ROWSIZE%4) || (COLSIZE%4))
	{
		printf("Matrix size should be in multiple of 4 for implemented domain decomposition. \n");
		return 1;
	}
	return 0;
}


int main(int argc, char** args)
{
	double start_time = 0;
	double total_time = 0;

	if(validate_input())
	{
		return 1;
	}

	#pragma omp parallel 
	{
			#pragma omp master
		{
			int cpu_threads = omp_get_num_threads();
       	 		printf ("Number of CPU Threads requested = %i\n",cpu_threads);
		}
	}

	init_arrays_matmul();
			
	start_time = mysecond();
		matrix_multiplication_multigpuoffload();
	total_time = (mysecond() - start_time);
			
	printf("Elapsed time (sec) : %f\n", total_time);
	printf("pC[0] : %f\n", pC[0]);
	printf("pC[(ROWSIZE*COLSIZE)-1] : %f\n", pC[(ROWSIZE*COLSIZE)-1]);
			
	free(pA);
	free(pB);
	free(pC);
		
	return 0;
}

