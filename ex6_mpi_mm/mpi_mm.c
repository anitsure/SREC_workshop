
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "mm.h"

void init_arrays_matmul_mpi(int np, int rank);

int main(int argc, char** argv)
{
	int rank, np;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD, &np); // assign total number of tasks 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // my rank

	MPI_Status status;

	printf (" number of processes : %d \n ", np) ;
		
	init_arrays_matmul_mpi(np, rank);
		
	MPI_Barrier(MPI_COMM_WORLD);
	double start = MPI_Wtime();

	//TODO: 0th task split pA and send to np tasks. (Scatter Matrix pA among all tasks)

	//TODO:  broadcast copy of pB to all tasks 
	
	// call to matrix multiplication function
	matrix_multiplication(np, rank, recA, recC);
	
	//TODO: 0th task gather result (recA) from all tasks. (Gather result pC from all task)

	double end = MPI_Wtime();  

	double time = end - start ;
	printf (" ****************** process %d : time = %f \n" , rank , time ) ;

	if (rank == 0) {

		printf("pC[0] : %f\n", pC[0]);
        printf("pC[(ROWSIZE*COLSIZE)-1] : %f\n", pC[(ROWSIZE*COLSIZE)-1]);

		free(pA);
        	free(pB);
	        free(pC);
		free(recA);
		free(recC);
	}

	MPI_Finalize();

	return 0;
}
