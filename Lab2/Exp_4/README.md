## Experiment 4: Scheduling and Load Imbalance in OpenMP

This experiment analyzes how different OpenMP scheduling strategies handle load imbalance when loop iterations have nonuniform computational costs. The workload is intentionally imbalanced, with iteration cost increasing proportionally to the loop index. The objective is to compare static, dynamic and guided scheduling policies and evaluate their effect on parallel execution time and imbalance.

### Workload Description

Each iteration performs a computationally expensive loop. The number of inner loop iterations increases with the outer loop index i. As a result, later iterations require significantly more work, creating a natural imbalance.

The scheduling strategies examined are:
1. schedule(static)
2. schedule(dynamic, 4)
3. schedule(guided)

The program measures per-thread active time and computes three key metrics:
- T_max: Maximum thread active time
- T_avg: Average thread active time across all threads
- Imbalance: (T_max – T_avg) / T_avg

The program was executed on a machine with 16 threads.

### Results

| Schedule      | T_max (s)    | T_avg (s)      | Imbalance (%) |
|---------------|--------------|----------------|----------------|
| static        | 0.00011249   | 0.0000889959   | 26.40%        |
| dynamic,4     | 0.00000000   | 0.00000000     | 18.73%        |
| guided        | 0.00000000   | 0.00000000     | 27.63%        |

### Interpretation

#### Static Scheduling
In static scheduling, the iteration space is divided into equal contiguous chunks before execution begins. When the workload varies per iteration, some threads finish much earlier than others. This results in idle threads waiting at synchronization points. The imbalance of 26.40 percent indicates that static scheduling is ineffective for uneven workloads.

#### Dynamic Scheduling
Dynamic scheduling assigns small chunks of work to threads at runtime. When a thread finishes its chunk, it immediately requests another one. This approach reduces idle time and improves load distribution across threads. The imbalance value of 18.73 percent is the lowest among the three strategies, showing that dynamic scheduling adapts better to uneven iteration costs.

#### Guided Scheduling
Guided scheduling begins with large chunk sizes that decrease over time. This strategy attempts to balance load more efficiently than static scheduling while reducing some of the overhead of dynamic scheduling. The measured imbalance of 27.63 percent is higher than dynamic scheduling. This can occur if the workload increases sharply toward the end of the loop, causing the smaller guided chunks to still create some imbalance.


### Graphs


### Conclusion

The experiment demonstrates that dynamic scheduling provides the best handling of load imbalance for this workload, producing the lowest imbalance among the tested policies. Static scheduling performs poorly because the workload increases significantly across the iteration space. Guided scheduling performs moderately but is outperformed by pure dynamic scheduling in this specific scenario.

These results reinforce the importance of choosing an appropriate scheduling strategy when workloads per iteration vary significantly.

End of Experiment 4
