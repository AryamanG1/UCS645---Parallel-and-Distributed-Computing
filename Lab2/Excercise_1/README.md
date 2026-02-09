# Exercise 1 Molecular Dynamics Force Calculation using OpenMP

This exercise evaluates the parallel performance of a simple molecular dynamics force computation using the Lennard-Jones potential. The objective is to measure the execution time under different thread configurations and observe the scalability of the OpenMP parallel region when computing particle interactions.

## Problem Description

A system of N = 1000 particles is randomly initialized in 3D space.  
For every interacting pair of particles, the Lennard-Jones potential is computed:

U(r) = 4ε[(σ/r)^12 − (σ/r)^6]

To avoid expensive long-range interactions, a cutoff radius of 2.5σ is applied.

The computation involves nested loops and is parallelized using OpenMP with a reduction clause to accumulate the potential energy without race conditions.

## Compilation Instructions

g++ -O3 -fopenmp Q1.cpp -o Q1

## Execution Instructions

Threads can be set either using the command-line argument or with the OpenMP environment variable.

Examples:

./Q1 1  
./Q1 2  
./Q1 4  
./Q1 8  
./Q1 16

or

export OMP_NUM_THREADS=4  
./Q1

## Experimental Results

The experiment was executed for multiple thread counts.  
The following table summarizes the measured execution times:

| Threads | Execution Time (s) |
|---------|---------------------|
| 1       | 0.00398287          |
| 2       | 0.00344072          |
| 4       | 0.00211315          |
| 8       | 0.00166481          |
| 16      | 0.00183414          |

## Speedup

Speedup S(p) = T1 / Tp

| Threads | Speedup |
|---------|----------|
| 1       | 1.00     |
| 2       | 1.16     |
| 4       | 1.88     |
| 8       | 2.39     |
| 16      | 2.17     |

## Observations

1. The program shows good scaling up to eight threads and achieves more than a 2× speedup.
2. The speedup drops slightly at 16 threads because the computation becomes memory-bound and thread scheduling overhead begins to dominate.
3. The use of the reduction clause ensures race-free accumulation of the total potential energy.
4. The execution time does not vary significantly with different runs, indicating stable performance.
5. The nested loop structure provides enough work to expose parallelism, but because the number of total interactions is moderate (about 500,000 pairs), scaling beyond 8 threads saturates.

## Conclusion

The molecular dynamics force calculation benefits from OpenMP parallelism, demonstrating clear performance improvement with increasing threads up to approximately eight threads. The reduction clause offers an efficient and thread-safe method for accumulating the potential energy. The experiment illustrates performance characteristics of short-range pair interactions and highlights limitations due to memory bandwidth and scheduling overhead at higher thread counts.
