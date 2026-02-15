# Parallel Correlation Matrix Computation

## Problem Statement

Given a matrix of size ny × nx containing m input vectors (rows),\
compute the correlation coefficient between every pair of input vectors.

For all 0 ≤ j ≤ i \< ny, compute the correlation between row i and row
j\
and store the result in the lower triangular matrix position:

result\[i + j \* ny\]

All arithmetic operations are performed using double precision.

------------------------------------------------------------------------

## Implementations

Three implementations are provided:

1.  Sequential baseline version\
2.  OpenMP parallel version\
3.  Optimized fast version (OpenMP + SIMD + -O3)

------------------------------------------------------------------------

## Compilation

``` bash
make
```

------------------------------------------------------------------------

## Execution

``` bash
./correlate <ny> <nx>
```

Example:

``` bash
./correlate 2000 2000
```

------------------------------------------------------------------------

## Performance Evaluation

Matrix Size Tested: 2000 × 2000

------------------------------------------------------------------------

### 1 Thread

Sequential Time: 4.32922 sec\
OpenMP Time: 3.84766 sec\
Fast Time: 4.07639 sec

------------------------------------------------------------------------

### 2 Threads

Sequential Time: 4.17719 sec\
OpenMP Time: 2.20747 sec\
Fast Time: 2.07414 sec

------------------------------------------------------------------------

### 4 Threads

Sequential Time: 4.20303 sec\
OpenMP Time: 1.32696 sec\
Fast Time: 1.19499 sec

------------------------------------------------------------------------

### 8 Threads

Sequential Time: 4.57222 sec\
OpenMP Time: 0.757956 sec\
Fast Time: 0.587033 sec

------------------------------------------------------------------------

## Speedup Analysis (Fast Version)

Speedup = T₁ / Tₙ

  Threads   Fast Time (sec)   Speedup
  --------- ----------------- ---------
  1         4.07639           1.00x
  2         2.07414           1.97x
  4         1.19499           3.41x
  8         0.587033          6.94x

Near-linear scaling is observed up to 8 threads.

------------------------------------------------------------------------

## perf Statistics (8 Threads)

CPUs utilized: \~2.43\
Instructions per cycle: \~1.27\
Branch miss rate: \~0.08%\
Total elapsed time: \~6.05 sec

------------------------------------------------------------------------

## Optimization Techniques Used

-   Precomputation of row means and normalization
-   Lower triangular computation only
-   OpenMP parallelization
-   Loop collapse for nested loops
-   SIMD reduction pragma
-   Compiler optimization flag -O3
-   Improved memory access locality

------------------------------------------------------------------------

## Observations

-   Sequential implementation scales quadratically with ny.
-   Parallel implementation significantly reduces execution time.
-   Speedup improves as thread count increases.
-   Memory bandwidth begins to limit scaling at higher thread counts.
-   SIMD improves inner loop performance.

------------------------------------------------------------------------

## Clean Build

``` bash
make clean
```
