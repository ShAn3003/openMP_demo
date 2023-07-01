#include <stdio.h>
#include <omp.h>
int x;
#pragma omp threadprivate(x)
int main()
{
    int tid, a;

    omp_set_num_threads(4);
    tid = omp_get_thread_num();
    a = -1;
    x = -2;
    printf("* * * * * * 1st serial region * * * * * *\n");
    printf("a = %d, x = %d, id = %d\n", a, x, tid);
    printf("\n");

    printf("---1st parallel region---\n");
/*firstprivate(a):
此子句用于在并行区域中将变量 a 设置为私有，
并将其初始值设置为主线程中的值。
每个线程在进入并行区域时都会复制一份 a 的初始值
，并在并行执行期间对其进行操作，而不会影响其他线程的副本。

private(tid):
此子句用于在并行区域中声明一个私有变量 tid，
该变量用于存储当前线程的线程ID。
每个线程都会拥有自己的 tid 变量副本
，使得每个线程可以独立地访问和操作它，
而不会干扰其他线程的副本。

copyin(x):
此子句用于在并行区域中将变量 x 设置为每个线程的共享值
。这意味着每个线程在进入并行区域时都会复制一份 x 的值，
并在并行执行期间共享这个值。
如果主线程在进入并行区域之前对 x 进行了修改，
这些修改将被复制到每个线程的副本中。
*/
#pragma omp parallel firstprivate(a) private(tid) copyin(x)
    {
        tid = omp_get_thread_num();
        printf("a = %d, x = %d, id = %d\n", a, x, tid);
        a = a + tid + 10;
        x = x + tid + 100;
        printf("a = %d, x = %d, a&x change, id = %d\n", a, x, tid);
        printf("\n");
    }

    tid = omp_get_thread_num();
    printf("* * * * * * 2nd serial region * * * * * *\n");
    printf("a = %d, x = %d, id = %d\n", a, x, tid);
    printf("\n");
    a = a + tid + 10;
    x = x + tid + 100;
    printf("a = %d, x = %d, a&x chagned, id = %d\n", a, x, tid);

    printf("\n");
    printf("---2nd parallel region---\n");
#pragma omp parallel firstprivate(a) private(tid)
    {
        tid = omp_get_thread_num();
        printf("2nd parallel: a = %d, x = %d, id = %d\n", a, x, tid);
        printf("\n");
/*
copyprivate(x, a):
 此子句用于在 single 块中复制 x 和 a 的值给单个线程
 （在这种情况下是主线程）。
 单个线程负责执行 single 块中的代码，
 并且对 x 和 a 的修改只会影响该线程的副本。
 其他线程将保持对 x 和 a 的原始副本的访问。
 */
#pragma omp single copyprivate(x, a)
        {
            printf("\n");
            printf("---2nd parallel region single block\n");
            tid = omp_get_thread_num();
            printf("a = %d, x = %d, id = %d\n", a, x, tid);
            a = a + tid + 10;
            x = x + tid + 100;
            printf("a = %d, x = %d, a&x chagned, id = %d\n", a, x, tid);
        }
        printf("---2nd parallel region after single\n");
        tid = omp_get_thread_num();
        printf("a = %d, x = %d, id = %d\n", a, x, tid);
    }
    printf("\n");
    printf("* * * * * * 3rd serial region * * * * * *\n");
    printf("a = %d, x = %d, id = %d\n", a, x, tid);
    return 0;
}