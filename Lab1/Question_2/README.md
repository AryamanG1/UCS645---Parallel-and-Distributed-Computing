# Synopsis Q2
## Matrix Multiplication

- I multiplied two large matrices and divided the work among threads.
- I first parallelized a single loop to distribute rows across threads.
- I then tried a two loop parallel version to spread the work more evenly.
- I compared both versions to see which structure allowed better performance under different thread counts.
