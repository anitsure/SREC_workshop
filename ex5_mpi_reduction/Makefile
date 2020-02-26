ROWS=100
COLS=100

mpi_reduction	:	mpi_reduction.c mm.c
	mpicc -o mpi_reduction mpi_reduction.c mm.c  -qsmp=omp -DROWSIZE=$(ROWS) -DCOLSIZE=$(COLS)

clean	:
	rm mpi_reduction
