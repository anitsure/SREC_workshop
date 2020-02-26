#include <stdio.h>
#include <omp.h>

// The helloWorld program to demonstrate OpenMP parallel directive, runtime library APIs and Environment variables.

int main()
{
	int i=0;
	int numThreads=0;

	// OpenMP runtime API
	numThreads = omp_get_num_threads();

	// OpenMP directive
	#pragma omp parallel
	{
		// OpenMP runtime API
		int threadNum = omp_get_thread_num();
		printf("Hello World from thread %d \n", threadNum);

	}
	return 0;
}
