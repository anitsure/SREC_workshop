
ROWS=10000
COLS=10000
CC=/home/users/gansys/hipc_tutorial/xlc_install/opt/ibm/xlC/16.1.1/bin/xlc
COMPFLAGS=-O3 -qhot -mcpu=power9 -mtune=power9 -maltivec

matmul_multigpu:	main.c mm.c helper.c
	${CC} -o matmul_multigpu main.c mm.c helper.c -qsmp=omp -qoffload ${COMPFLAGS} -qtgtarch=sm_70 -lcudart -L/usr/local/cuda/lib64 -DROWSIZE=$(ROWS) -DCOLSIZE=$(COLS) -D__OPENMP_GPU__

clean	:
	rm matmul_multigpu
