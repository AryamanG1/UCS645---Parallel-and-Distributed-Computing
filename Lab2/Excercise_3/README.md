# Exercise 3 Heat Diffusion Simulation using OpenMP

This exercise implements the two dimensional heat diffusion equation using an iterative stencil based update. The grid consists of 1500 × 1500 points, and heat is propagated for 1500 time steps. OpenMP is used to parallelize the computation over the two dimensional grid using the collapse(2) directive.

## Problem Description

The simulation uses the classical five point stencil.  
For every interior point of the grid T, the temperature at the next timestep is computed as:

Tnew[i][j] = 0.25 × (T[i+1][j] + T[i−1][j] + T[i][j+1] + T[i][j−1])

The top boundary is fixed at 100 degrees. All other values start at zero.  
After each iteration the T and Tnew matrices are swapped.  
The computation is highly parallel as each grid point depends only on its four neighbors.

## Compilation Instructions

g++ -O3 -fopenmp Q3.cpp -o Q3

## Execution Instructions

The program accepts the number of threads as a command line argument.

Examples:

./Q3 1  
./Q3 2  
./Q3 4  
./Q3 8  
./Q3 16  
./Q3 20

## Experimental Results

The following execution times were recorded for the given thread counts:

| Threads | Execution Time (s) |
|---------|---------------------|
| 1       | 8.63237             |
| 2       | 4.74272             |
| 4       | 3.93632             |
| 8       | 3.76966             |
| 16      | 4.10367             |
| 20      | 4.07943             |

## Observations

1. The program shows significant speedup when increasing from one thread to four threads.
2. Performance improves up to eight threads, which gives the best execution time among all configurations.
3. Beyond eight threads, execution time increases slightly. This indicates that the computation becomes memory bandwidth bound and additional threads cannot be utilized effectively.
4. The collapse(2) directive enables parallelization across both dimensions of the grid which distributes work evenly.
5. The working set of the 1500 × 1500 grid exceeds cache capacity, causing memory traffic to dominate and limit scaling at high thread counts.

## Conclusion

The heat diffusion stencil demonstrates good scalability up to a moderate number of threads. The performance saturates near eight threads due to memory bandwidth limitations. This experiment highlights how stencil based computations benefit from shared memory parallelism but also face bottlenecks from memory subsystem constraints when thread counts become large.
