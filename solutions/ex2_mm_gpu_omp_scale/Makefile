
ROWS=10000
COLS=10000
COMPFLAGS=-O3 -qhot -mcpu=power9 -mtune=power9 -maltivec

matmul_multigpuoffload	:	main.c mm.c helper.c
	xlc -o matmul_multigpuoffload main.c mm.c helper.c -qsmp=omp -qoffload ${COMPFLAGS} -qtgtarch=sm_70 -lcudart -L/usr/local/cuda/lib64 -DROWSIZE=$(ROWS) -DCOLSIZE=$(COLS) -D__OPENMP_GPU__

clean	:
	rm matmul_multigpuoffload 
