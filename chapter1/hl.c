#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int i, j, k, nthreads, n_running_threads, num_steps;
    double x, tsum, sum, step, start_time, end_time, used_time;

    nthreads = 4;
    num_steps = 500;
    start_time = omp_get_wtime();
    omp_set_num_threads(nthreads);
    step = 1.0 / num_steps;
    sum = 0.0;
/*
private(x, i)指示在并行区域中为每个线程创建私有的x和i变量。
每个线程都有自己的x和i副本，这样可以避免多个线程之间的数据竞争。
default(shared)指示将所有未明确指定共享性的变量视为共享变量。
这意味着在并行区域中，除了私有变量之外，其他变量都将被视为共享变量，多个线程可以访问和修改这些共享变量。
*/
#pragma omp parallel private(x, i) default(shared)
    {
        n_running_threads = omp_get_num_threads();
/*
reduction(+ : sum) 指示将归约操作应用于共享变量 sum，
并且该操作是求和（+）。
这意味着在并行执行的每个线程中，
都会有一个私有的 sum 变量，
每个线程都会计算自己的部分和，
然后将这些部分和相加以得到最终的结果。
*/
#pragma omp for reduction(+ : sum)
        for (i = 0; i < num_steps; i++)
        {
            for (j = 0; j < num_steps; j++)
            {
                for (k = 0; k < num_steps; k++)
                {
                    x = (i + j + k + 0.5) * step;
                    sum = sum + sin(tan(log(abs(sin(cos(x + 20.0) + 2.0) + 3.0) + 4.0)));
                }
            }
        }
    }
    tsum = step * sum;
    end_time = omp_get_wtime();
    used_time = end_time - start_time;
    printf("used_time = %lf second\n", used_time);
    printf("nthreads = %d num_steps = %d\n", n_running_threads, num_steps);
    printf("tsum = %lf\n", tsum);
    return 0;
}
