// Example 4 : point-to-point communication

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int rank, np;
	int sbuff, rbuff;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD, &np); // assign total number of tasks 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // my rank

	MPI_Status status;

	sbuff = rank;
	rbuff = -1;

	if (rank== 0) 
	{
	    printf (" number of processes : %d \n ", np) ;
	}

	
	// share neighbour information
	// TODO: Write MPI send and receive functions to share rank with neighbour.
	// TODO : First try with 2 processes later write program for more than 2 processes

	// TODO : Handle boundary condition

	MPI_Finalize();

	return 0;
}
