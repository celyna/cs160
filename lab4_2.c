#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long steps = 100000;

int main (int argc, char **argv) {
    double pi;
    //double total_sum;
    double start;
    double run;
    double step = 1.0 / (double) steps;
    
    int i;
    for (i = 1; i <= 8; i++) {
        start = omp_get_wtime();
        omp_set_num_threads(i);
        //double total_sum = 0.0;
        double sum = 0.0;
        
        int j;

        #pragma omp parallel for reduction(+:sum)
        for (j = 0; j < steps; j++) {
            double x = (j + 0.5) / (double) steps;

            sum += 4.0 / (1.0 + x * x);
        }
        
        pi = step * sum;

        run = omp_get_wtime() - start;

        printf("pi is %f in %f seconds with %d with threads\n", pi, run, i);
    
    }

    return 0;
}