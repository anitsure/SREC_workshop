
#!/bin/bash

echo "Running MPI point-to-point example" 
mpirun -np 4 --hostfile hostlist -pami_noib ./mpi_p2p
