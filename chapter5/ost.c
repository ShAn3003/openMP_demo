#include <stdio.h>
#include <omp.h>

int main()
{
    int tid, nthreads;

    omp_set_num_threads(2);

#pragma omp parallel private(tid, nthreads)
    {
#pragma omp sections nowait
        // 有了nowait之后执行完子节1，之后不用等待2和3执行完，可以执行下一块
        {
#pragma omp section
            {
                tid = omp_get_thread_num();
                nthreads = omp_get_num_threads();
                printf("section 1: nthreads = %d, tid = %d\n", nthreads, tid);
            }

#pragma omp section
            {
                tid = omp_get_thread_num();
                nthreads = omp_get_num_threads();
                printf("section 2: nthreads = %d, tid = %d\n", nthreads, tid);
            }

#pragma omp section
            {
                tid = omp_get_thread_num();
                nthreads = omp_get_num_threads();
                printf("section 3: nthreads = %d, tid = %d\n", nthreads, tid);
            }
        }
    }
    return 0;
}