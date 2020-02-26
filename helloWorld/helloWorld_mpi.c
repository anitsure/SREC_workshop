

#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
	int myrank;
	int comm_size;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	printf("my rank is : %d of %d\n", myrank, comm_size);

	MPI_Finalize();
	return 0;
}
