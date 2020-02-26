#!/bin/bash

echo "Compiling helloWorld"
mpicc -o helloWorld_mpi helloWorld_mpi.c 

echo "Running helloWorld with 4 tasks"

mpirun -pami_noib -np 4 --hostfile ./hostlist ./helloWorld_mpi 

