
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "mm.h"

void init_arrays_matmul_mpi(int np, int pid);

int main(int argc, char** argv)
{
	int pid, np, msize;

	msize = COLSIZE;
	#ifdef MPI_MM_GPU
		int gpuid, ng;
		ng = 4;
	#endif

    MPI_Init(&argc,&argv);

    MPI_Comm_size(MPI_COMM_WORLD, &np); // assign total number of tasks 
    MPI_Comm_rank(MPI_COMM_WORLD, &pid); // my rank

	MPI_Status status;

    printf (" number of processes : %d \n ", np) ;
		
	init_arrays_matmul_mpi(np, pid);
		
	MPI_Barrier(MPI_COMM_WORLD);
	double start = MPI_Wtime();

	MPI_Bcast ( &msize, 1 , MPI_INT , 0 , MPI_COMM_WORLD ) ;
	printf ("  msize/np : %d \n " , msize/np) ;

	//0th task split pA and send to np tasks.
	MPI_Scatter( pA , ROWSIZE/np * COLSIZE, MPI_DOUBLE , recA , ROWSIZE/np * COLSIZE, MPI_DOUBLE , 0, MPI_COMM_WORLD ) ;

   // for (int i=0; i <  n*(n/p) ; i++)
//		printf (" process %d recA [%d] = % f \n " , pid , i , recA[i] ) ;

	// send copy of pB to all tasks 
	MPI_Bcast ( pB, ROWSIZE * COLSIZE, MPI_DOUBLE , 0 , MPI_COMM_WORLD );

//    for (int i=0; i < (n*n) ; i++)
//		printf (" process %d pB [%d] = % f \n " , pid , i , pB[i] ) ;

	#ifdef MPI_MM_GPU
		gpuid = pid*ng/np;
		matrix_multiplication_gpuoffload(gpuid, np, pid, recA, recC);
	#else // run on CPU
		matrix_multiplication(np, pid, recA, recC);
	#endif
	
	//0th task gather result (recA) from all tasks.
	MPI_Gather( recC, ROWSIZE/np * COLSIZE, MPI_DOUBLE, pC, ROWSIZE/np * COLSIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD); 
	double end = MPI_Wtime();  

	double time = end - start ;
	printf (" ********** process %d : time = %f \n" , pid , time ) ;

	if (pid == 0) {
//		print_matrix(pC);	

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
