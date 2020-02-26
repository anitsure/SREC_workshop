
#!/bin/bash

echo "Running MPI Reduction program"
mpirun -np 4 --hostfile hostlist -pami_noib ./mpi_reduction
