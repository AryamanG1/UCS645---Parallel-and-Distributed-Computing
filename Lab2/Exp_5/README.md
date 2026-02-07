## Experiment 5: Synchronization Overhead (critical, atomic, reduction)

This experiment evaluates the overhead of different synchronization mechanisms in OpenMP by comparing the execution times of a shared summation implemented using:

1. Critical Section
2. Reduction

Each method represents a different point in the performance spectrum of synchronization:

- Critical Section forces strict mutual exclusion. Only one thread can update the shared variable at a time.
- Reduction allows each thread to maintain a private partial sum and combines them efficiently at the end.

The objective of the experiment is to measure and compare the performance cost of each approach.

### Results

The program was executed on a system supporting multiple threads. The following times were recorded:

| Method            | Time (s)       |
|-------------------|----------------|
| Critical Section  | 1.89982        |
| Reduction         | 0.00211208     |

The relative overhead factor of the critical section compared to reduction is:

Overhead Factor = 899.498 times slower

### Interpretation

#### Critical Section
The critical section uses a software lock that ensures only one thread at a time can update the shared sum. As the number of threads increases, contention for the lock rises sharply. Most threads remain idle while waiting for access to the protected region. This results in extremely poor scalability and very high execution time.

The measured time of 1.89982 seconds confirms that the critical section becomes a significant bottleneck under contention.

#### Reduction
The reduction clause allows each thread to accumulate its own partial sum independently. At the end of the loop, the private values are merged into the final shared sum using optimized tree-based hardware or compiler-level mechanisms. Since threads do not need to wait for one another during the loop, reduction demonstrates near-linear scalability.

The observed time of 0.00211208 seconds reflects this efficient behavior.

### Conclusion

Reduction provides the best performance for parallel summation because it avoids synchronization during the loop. Critical sections, on the other hand, serialize the computation and introduce significant waiting time, making them unsuitable for high-thread-count scenarios.

This experiment clearly demonstrates the performance spectrum:

1. Reduction (fastest)
2. Atomic operations (intermediate, not shown in this output)
3. Critical Section (slowest)

