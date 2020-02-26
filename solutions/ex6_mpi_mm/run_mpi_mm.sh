
#!/bin/bash

echo "Running MPI MM on CPU"
mpirun -np 4 --hostfile hostlist -pami_noib ./mpi_mm 
#mpirun -np 4 --hostfile hostlist -pami_noib --report-bindings ./mpi_mm 
