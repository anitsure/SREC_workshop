
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "mm.h"

void init_arrays_matmul_mpi(int np, int rank);

int main(int argc, char** argv)
{
	int rank, np;
	double local_sum = 0;
	double sum = 0;

	int i=0;
	int j=0;
	
	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD, &np); // assign total number of tasks 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // my rank

	MPI_Status status;

	init_arrays_matmul_mpi(np, rank);

	if(0 == rank){
    	    printf ("Number of processes : %d \n", np) ;
	}
		
	MPI_Barrier(MPI_COMM_WORLD);
	double start = MPI_Wtime();

	//0th task split pA and send to np tasks.
	MPI_Scatter( pA , ROWSIZE/np * COLSIZE, MPI_DOUBLE , recA , ROWSIZE/np * COLSIZE, MPI_DOUBLE , 0, MPI_COMM_WORLD ) ;

	for (i=0; i<ROWSIZE/np; i++)
	{
		for (j=0; j<COLSIZE; j++)
		{
			local_sum += recA(i,j);
		}
	}

	printf("local_sum from rank %d : %f\n", rank, local_sum);

	//TODO: Experiment 1 : Add MPI reduction call to get global sum on ROOT task.
	
	//TODO: Experiment 2 : Add MPI reduction call to get global sum on all task

	printf("Global sum from rank %d: %f\n", rank, sum);
	
	double end = MPI_Wtime();  

	double time = end - start ;
	printf (" ********************* process %d : time = %f \n" , rank , time ) ;

	if (rank == 0) {


		free(pA);
		free(recA);
	}

	MPI_Finalize();

	return 0;
}
