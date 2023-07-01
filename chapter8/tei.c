#include <stdio.h>
#include <omp.h>

int main()
{
    omp_set_num_threads(4);
#pragma omp parallel
    {
        printf("A ");

#pragma omp task // 在并行的程序中创建任务，使得并行中的代码不一定按顺序执行
        printf("race(thread id = %d)\n", omp_get_thread_num());

        printf("car ");
    }
    return 0;
}