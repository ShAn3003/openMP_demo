#include <stdio.h>
#include <omp.h>

int main()
{
    omp_set_nested(1);  // 开启嵌套
    omp_set_dynamic(0); // 关闭动态

    printf("nested region(1 or 0): %d\n", omp_get_nested());

#pragma omp parallel num_threads(2) // 开启了两个线程的并行
    {
        if (0 == omp_get_thread_num()) // 如果并行的线程号为0,则设置线程为4
        {
            omp_set_num_threads(4);
        }
        else // 如果并行的线程不为0,则设置线程为3
        {
            omp_set_num_threads(3);
        }
#pragma omp master // 下一句代码在主线程执行
        printf("* * * * * outer zone: active_levle = %d, team_size = %d\n", omp_get_active_level(), omp_get_team_size(omp_get_active_level()));
        // 输出两次，因为开了两个线程的并行
        printf("outer: thread_ID = %d, threads_in_team = %d\n", omp_get_thread_num(), omp_get_num_threads());
#pragma omp parallel
        // 嵌套并行
        {
#pragma omp master
            printf("-----inner zone: active_level = %d, team_size = %d\n", omp_get_active_level(), omp_get_team_size(omp_get_active_level()));
            // 在0号线程再次开启并行，并行3次；在1号线程同样也开启并行，4个线程
            printf("inner: thread_ID = %d, threads_in_team = %d\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }
    return 0;
}