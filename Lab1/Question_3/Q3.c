#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]) {

    int threads = atoi(argv[1]);
    long steps = 10000000;
    double step = 1.0 / steps;
    double sum = 0.0;

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(threads) reduction(+:sum)
    for (long i = 0; i < steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    double pi = step * sum;
    double end = omp_get_wtime();

    printf("Threads: %d  Pi: %.10f  Time: %f seconds\n", threads, pi, end - start);

    return 0;
}
