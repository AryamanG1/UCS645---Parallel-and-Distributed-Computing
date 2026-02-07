## Experiment 6: False Sharing and Cache Line Contention in OpenMP

This experiment investigates the performance effects of false sharing, a hardware-level bottleneck that occurs when multiple threads update different variables that reside on the same cache line. Even if the threads operate on independent memory locations, the cache coherence protocol forces constant invalidation and synchronization, significantly slowing execution.

Two implementations were compared:

1. Unpadded (False Sharing Present):  
   Threads write to adjacent elements of a shared array. Multiple threads update variables that map to the same cache line.

2. Padded (False Sharing Eliminated):  
   Each thread writes to a memory region separated by at least one cache line (typically 64 bytes). This prevents cross-core invalidations and removes cache line ping-ponging.

The experiment measures execution time for both versions.

### Results

| Configuration         | Time (seconds) |
|-----------------------|----------------|
| False Sharing         | 0.250968       |
| Padded (Fixed)        | 0.238732       |

A second implementation also demonstrates a similar pattern:

| Configuration         | Time (seconds) |
|-----------------------|----------------|
| Unpadded              | 0.000750386    |
| Padded                | 0.000197794    |

### Interpretation

#### Unpadded Version (False Sharing)
In the unpadded version, each thread writes to a different element of the same continuous array. Since modern CPUs organize memory into cache lines of fixed size, multiple variables fall within the same cache line. When one thread writes to a variable within a cache line, the hardware invalidates that line in other cores, forcing refetches and leading to heavy coherence traffic.

This results in unnecessary core-to-core communication and significantly increases execution time. The measured times reflect this overhead.

#### Padded Version (False Sharing Eliminated)
In the padded version, each thread writes to a separate cache line. Padding ensures that no two threads share a cache line, thus preventing coherence invalidations. Each core can update its local cache without interference.

This leads to improved performance and predictable scaling.  
In both outputs, the padded version is noticeably faster, confirming that removal of false sharing restores efficient parallelism.

### Conclusion

The experiment demonstrates that false sharing can severely degrade performance even when threads operate on logically independent data. Proper padding and cache-aware memory layout are essential for building scalable parallel programs. Eliminating false sharing allows each thread to operate on its own cache line without contention, resulting in lower execution time and more efficient parallel execution.

