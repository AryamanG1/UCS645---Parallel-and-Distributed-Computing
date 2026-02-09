# Exercise 2 Smith–Waterman Sequence Alignment using OpenMP

This exercise implements the Smith–Waterman local sequence alignment algorithm and evaluates the performance impact of OpenMP parallelization. The dynamic programming matrix is computed using anti diagonal parallelism, where each diagonal of the matrix is independent and can be processed in parallel.

## Problem Description

Two DNA sequences are aligned using the Smith–Waterman algorithm.  
The scoring system used is as follows:

Match score      = 2  
Mismatch penalty = −1  
Gap penalty      = −1  

The dynamic programming matrix H is initialized to zero and filled using local alignment recurrence rules. OpenMP is used to parallelize the computation across anti diagonals.

## Compilation Instructions

g++ -O3 -fopenmp Q2.cpp -o Q2

## Execution Instructions

The number of threads can be provided as a command line argument.

Examples:

./Q2 1  
./Q2 2  
./Q2 4  
./Q2 8  
./Q2 16

If no argument is given, the program will use the default thread count provided by the OpenMP runtime.

## Experimental Results

Execution times for different thread counts are listed below:

| Threads | Execution Time (s) |
|---------|---------------------|
| 1       | 0.000020171         |
| 2       | 0.000544607         |
| 4       | 0.000944290         |
| 8       | 0.001533320         |
| 16      | 0.001824380         |

## Observations

1. The execution time increases with thread count instead of decreasing.  
2. The reason is that the problem size is extremely small, containing only an 8×8 dynamic programming matrix.  
3. The actual work per iteration is too small to amortize the OpenMP scheduling and thread creation overhead.  
4. Parallelization overhead dominates the computation at higher thread counts, resulting in slower execution for larger thread counts.  
5. The fastest execution is obtained with a single thread due to the low computation workload.

## Conclusion

The Smith–Waterman algorithm can benefit from parallelization for larger sequence lengths. However, for very small sequences, OpenMP introduces more overhead than benefit. This experiment demonstrates that parallel performance depends heavily on the size of the problem and that OpenMP is most effective for large dynamic programming matrices where sufficient parallel work exists.
