
ROWS=3000
COLS=3000
COMPFLAGS=-O3 


matmul	:	main.c mm.c
	gcc -o matmul.gcc main.c mm.c -DROWSIZE=$(ROWS) -DCOLSIZE=$(COLS) ${COMPFLAGS} 

matmul_cpu	:	main.c mm.c
	gcc -o matmul_cpu.gcc  main.c mm.c -fopenmp -DROWSIZE=$(ROWS) -DCOLSIZE=$(COLS) ${COMPFLAGS} -D__OPENMP_CPU__

clean	:
	rm matmul.gcc matmul_cpu.gcc
