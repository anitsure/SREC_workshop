ROWS=1000
COLS=1000

mpi_mm	:	mpi_mm.c mm.c
	mpicc -o mpi_mm mpi_mm.c mm.c  -qsmp=omp -DROWSIZE=$(ROWS) -DCOLSIZE=$(COLS)

clean	:
	rm mpi_mm 
