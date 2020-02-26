ROWS=10000
COLS=10000

all	:	mpi_matmul mpi_matmul_gpu

mpi_matmul	:	mpi_mm.c mm.c
	/opt/ibm/spectrum_mpi/bin/mpicc -o mpi_matmul mpi_mm.c mm.c  -qsmp=omp -DROWSIZE=$(ROWS) -DCOLSIZE=$(COLS)

mpi_matmul_gpu	:	mpi_mm.c mm.c gpuoffload.c 
	OMPI_CC=/home/users/gansys/hipc_tutorial/xlc_install/opt/ibm/xlC/16.1.1/bin/xlc /opt/ibm/spectrum_mpi/bin/mpicc -pami_noib -o mpi_matmul_gpu mpi_mm.c mm.c gpuoffload.c -qsmp=omp -qoffload -qtgtarch=sm_70 -lcudart -L/usr/local/cuda/lib64 -DROWSIZE=$(ROWS) -DCOLSIZE=$(COLS) -DMPI_MM_GPU

clean	:
	rm mpi_matmul mpi_matmul_gpu
