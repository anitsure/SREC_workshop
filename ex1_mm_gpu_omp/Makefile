
ROWS=3000
COLS=3000
CC=/home/users/gansys/hipc_tutorial/xlc_install/opt/ibm/xlC/16.1.1/bin/xlc
COMPFLAGS=-O3 -qhot -mcpu=power9 -mtune=power9 -maltivec


matmul	:	main.c mm.c
	${CC} -o matmul main.c mm.c -DROWSIZE=$(ROWS) -DCOLSIZE=$(COLS) ${COMPFLAGS} 

matmul_cpu	:	main.c mm.c
	${CC} -o matmul_cpu main.c mm.c -fopenmp -DROWSIZE=$(ROWS) -DCOLSIZE=$(COLS) ${COMPFLAGS} -D__OPENMP_CPU__

clean	:
	rm matmul matmul_cpu
