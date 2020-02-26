#!/bash/bin

/opt/ibm/spectrum_mpi/bin/mpirun -np 4 --hostfile hostlist -pami_noib --report-bindings ./mpi_matmul_gpu
