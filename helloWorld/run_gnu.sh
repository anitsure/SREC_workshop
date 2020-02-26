#!/bin/bash

echo "Compiling helloWorld"
gcc -o helloWorld helloWorld.c -fopenmp

echo "Running helloWorld with 4 threads"

# OpenMP environment variable
export OMP_NUM_THREADS=4

./helloWorld 

