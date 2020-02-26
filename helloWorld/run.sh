#!/bin/bash

echo "Compiling helloWorld"
xlc -o helloWorld helloWorld.c -qsmp=omp

echo "Running helloWorld with 4 threads"

# OpenMP environment variable
export OMP_NUM_THREADS=4

./helloWorld 

