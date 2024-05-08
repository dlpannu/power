#include <stdio.h>
#include <omp.h>

int main() {
    int n, i, sum = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    #pragma omp parallel shared(sum, n)
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int chunk_size = n / num_threads;

        int start = thread_id * chunk_size + 1;
        int end = (thread_id == num_threads - 1) ? n : start + chunk_size - 1;

        #pragma omp atomic
        for (i = start; i <= end; i++) {
            sum += i;
        }

        #pragma omp barrier

        if (thread_id == 0) {
            printf("Sum of natural numbers from 1 to %d is: %d\n", n, sum);
        }
    }

    return 0;
}
