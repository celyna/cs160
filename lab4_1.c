#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long steps = 100000;

int main (int argc, char **argv) {    
    double pi;
    double total_sum;
    double start;
    double run;
    double step = 1.0 / (double) steps;
    
    int i;
    for (i = 1; i <= 8; i++)
    {
        start = omp_get_wtime();
        omp_set_num_threads(i);
        total_sum = 0.0;

        #pragma omp parallel 
        {

            int thread_id = omp_get_thread_num();
            int threads = omp_get_num_threads();
            double x = 0.0;
            double sum = 0.0;
            
            int j;
            for (j = thread_id; j < steps; j += threads) {
                x = (j + 0.5) * step;
                sum = sum + 4.0 / (1.0 + x * x);
            }
            total_sum += sum;

        }
        pi = step * total_sum;

        run = omp_get_wtime() - start;

        printf("pi is %f in %f seconds with %d threads\n", pi, run, i);
    }

    return 0;
}