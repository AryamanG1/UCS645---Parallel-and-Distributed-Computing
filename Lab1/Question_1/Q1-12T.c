#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]) {

    int threads = 12;
    int N = 1 << 16;

    double *X = malloc(N * sizeof(double));
    double *Y = malloc(N * sizeof(double));
    double a = 3;

    for (int i = 0; i < N; i++) {
        X[i] = 1.0;
        Y[i] = 2.0;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < N; i++) {
        X[i] = a * X[i] + Y[i];
    }

    double end = omp_get_wtime();

    printf("Threads: %d  Time: %f seconds\n", threads, end - start);

    free(X);
    free(Y);

    return 0;
}
