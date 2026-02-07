#include <iostream>
#include <omp.h>
#include <chrono>
#include <vector>
#include <iomanip>
using namespace std;

double calculate_pi_parallel(long long steps, int num_threads) {
    double step = 1.0 / (double)steps;
    double sum = 0.0;

    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel num_threads(num_threads)
    {
        double x;
        double local_sum = 0.0;

        #pragma omp for
        for (long long i = 0; i < steps; i++) {
            x = (i + 0.5) * step;
            local_sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp atomic
        sum += local_sum;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;

    return diff.count();
}

int main() {
    int max_cores = 23;
    long long base_steps = 100000000;

    cout << fixed << setprecision(4);

    long long strong_total_steps = 500000000;

    cout << "--- STRONG SCALING ---" << endl;
    cout << left << setw(12) << "Cores" << setw(15) << "Time (s)" << "Speedup" << endl;

    double t_serial_strong = calculate_pi_parallel(strong_total_steps, 1);
    cout << setw(12) << "1 (Serial)" << setw(15) << t_serial_strong << "1.00x" << endl;

    for (int n = 4; n <= max_cores; n += 4) {
        double p_time = calculate_pi_parallel(strong_total_steps, n);
        cout << setw(4) << n << " Cores" << "   "
             << setw(15) << p_time << (t_serial_strong / p_time) << "x" << endl;
    }

    cout << "\n--- WEAK SCALING ---" << endl;
    cout << left << setw(12) << "Cores" << setw(15) << "Total Work"
         << setw(15) << "Time (s)" << "Efficiency" << endl;

    double t_serial_weak = calculate_pi_parallel(base_steps, 1);
    cout << setw(12) << "1 (Serial)" << setw(15) << base_steps
         << setw(15) << t_serial_weak << "100%" << endl;

    for (int n = 4; n <= max_cores; n += 4) {
        long long current_work = base_steps * n;
        double p_time = calculate_pi_parallel(current_work, n);
        double efficiency = (t_serial_weak / p_time) * 100.0;

        cout << setw(4) << n << " Cores" << "   "
             << setw(15) << current_work
             << setw(15) << p_time
             << efficiency << "%" << endl;
    }

    return 0;
}
