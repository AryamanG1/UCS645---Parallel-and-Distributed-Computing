# UCS645 Parallel and Distributed Computing  
## Lab 2 OpenMP Performance Experiments

This lab contains a structured set of experiments that explore fundamental and advanced performance behaviors in OpenMP based multicore programs. Each experiment focuses on a specific aspect such as execution time, speedup, scheduling, synchronization overhead, cache behavior and memory bandwidth limits. Together, these experiments provide a complete performance profile of OpenMP programs on modern multicore hardware.

## Experiment 1 Execution Time and Basic Speedup

This experiment measures the execution time of a simple vector addition under different thread counts. The goal is to observe improvement in performance due to parallelism and to identify points where performance saturates due to memory or scheduling overhead.

## Experiment 2 Speedup and Parallel Efficiency

This experiment extends the results of Experiment 1 by computing the speedup and efficiency metrics.  
Speedup S(p) equals T1 divided by Tp.  
Efficiency E(p) equals S(p) divided by p.  
The objective is to study how effectively the system utilizes additional cores.

## Experiment 3 Strong Scaling and Weak Scaling

Strong scaling keeps the problem size constant while increasing the number of threads.  
Weak scaling increases the problem size proportionally with the number of threads.  
This experiment highlights compute bound and memory bound limitations and the factors that prevent ideal scaling.

## Experiment 4 Scheduling and Load Imbalance

This experiment compares various OpenMP scheduling policies including static scheduling, dynamic scheduling and guided scheduling.  
Workloads with varying iteration costs reveal thread imbalances.  
The experiment measures per thread timing and quantifies imbalance to show how scheduling influences performance.

## Experiment 5 Synchronization Overhead

This experiment evaluates the cost of synchronization using critical sections, atomic operations and reduction.  
Critical sections serialize updates and scale poorly.  
Atomic operations reduce overhead but remain slower than reduction.  
Reduction provides near optimal performance due to efficient private accumulation and final combination.

## Experiment 6 False Sharing and Cache Line Contention

This experiment demonstrates the performance degradation that occurs when threads update variables that reside on the same cache line.  
The unpadded version suffers from hardware level invalidations across caches.  
The padded version eliminates false sharing by isolating each thread’s data into independent cache lines.  
The comparison highlights the importance of cache aware programming.

## Experiment 7 Memory Bandwidth Saturation Triad Kernel

Using the classical Triad kernel A equals B plus s times C, this experiment measures execution time, memory bandwidth and speedup across multiple threads.  
The results show that memory bandwidth limits performance beyond a certain number of threads.  
Although bandwidth increases with thread count, the speedup eventually plateaus due to memory subsystem saturation.

## Directory Structure

Each experiment folder contains the OpenMP source file, the compiled executable, the recorded output and the analysis.  
The typical folder layout is as follows

Exp_1  
Exp_2  
Exp_3  
Exp_4  
Exp_5  
Exp_6  
Exp_7

## Compilation

All experiment codes can be compiled using the following command

g++ -O3 -fopenmp file.cpp -o output

## Execution

Thread count can be controlled using

export OMP_NUM_THREADS value  
./output

Some programs automatically sweep across available thread counts.

## Conclusion

Lab 2 provides a comprehensive study of OpenMP performance behavior by covering execution time, speedup, efficiency, scheduling effects, synchronization overhead, false sharing and memory bandwidth saturation.  
The experiments reinforce the concepts of parallel scalability and highlight the hardware and software factors that influence the performance of multicore systems.

End of Lab 2 README
