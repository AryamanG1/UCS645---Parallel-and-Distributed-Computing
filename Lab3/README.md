# Parallel Correlation Matrix Computation

## Problem Statement

Given a matrix of size **ny × nx** containing **m input vectors (rows)**,  
compute the **correlation coefficient** between every pair of input vectors.

For all `0 ≤ j ≤ i < ny`, compute:

    correlation(row_i, row_j)

Store the result in the lower triangular matrix location:

    result[i + j * ny]

All arithmetic operations are performed using **double precision**.

---

## Implementations

Three versions are implemented:

| Version      | Description                                           |
|--------------|-------------------------------------------------------|
| Sequential   | Baseline single-threaded implementation               |
| OpenMP       | Multi-threaded parallel implementation                |
| Fast         | OpenMP + SIMD + -O3 compiler optimizations            |

---

## Compilation

```bash
make
```

---

## Execution

```bash
./correlate <ny> <nx>
```

Example:

```bash
./correlate 2000 2000
```

---

# Performance Evaluation

**Matrix Size Tested:** 2000 × 2000

---

## Execution Time Comparison

### 1 Thread

| Version     | Time (sec) |
|------------|------------|
| Sequential | 4.32922    |
| OpenMP     | 3.84766    |
| Fast       | 4.07639    |

### 2 Threads

| Version     | Time (sec) |
|------------|------------|
| Sequential | 4.17719    |
| OpenMP     | 2.20747    |
| Fast       | 2.07414    |

### 4 Threads

| Version     | Time (sec) |
|------------|------------|
| Sequential | 4.20303    |
| OpenMP     | 1.32696    |
| Fast       | 1.19499    |

### 8 Threads

| Version     | Time (sec) |
|------------|------------|
| Sequential | 4.57222    |
| OpenMP     | 0.757956   |
| Fast       | 0.587033   |

---

# Speedup Analysis (Fast Version)

Speedup formula:

    Speedup = T1 / Tn

| Threads | Fast Time (sec) | Speedup |
|---------|-----------------|----------|
| 1       | 4.07639         | 1.00×    |
| 2       | 2.07414         | 1.97×    |
| 4       | 1.19499         | 3.41×    |
| 8       | 0.587033        | 6.94×    |

Parallel Efficiency (8 threads):

    Efficiency = 6.94 / 8 ≈ 86.7%

---

#  perf Statistics (8 Threads)

| Metric                     | Value     |
|----------------------------|-----------|
| CPUs utilized              | ~2.43     |
| Instructions per cycle     | ~1.27     |
| Branch miss rate           | ~0.08%    |
| Total elapsed time         | ~6.05 sec |

---

#  Optimization Techniques Used

- Precomputation of row means and normalization  
- Lower triangular computation only  
- OpenMP parallelization  
- Loop collapse for nested loops  
- SIMD reduction pragma  
- Compiler optimization flag -O3  
- Improved memory access locality  

---

#  Observations

- Time complexity grows approximately O(ny² × nx).
- Parallel implementation significantly reduces execution time.
- Speedup scales nearly linearly up to 8 threads.
- Memory bandwidth begins to limit scaling at higher thread counts.
- SIMD improves inner loop arithmetic throughput.

---

##  Clean Build

```bash
make clean
```

