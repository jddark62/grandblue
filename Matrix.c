#include <stdio.h>
#include <omp.h>

int main()
{
    int n = 6;
    int a[6] = {1, 3, 5, 7, 9, 11};
    int b[6] = {2, 4, 6, 8, 10, 12};
    int c[6];
    int d[6];
    c[0] = a[0] + b[0];

    for(int i = 1; i < n; i++)
        c[i] = a[i] + b[i] + c[i-1];

    int prefix_sum = 0;
    #pragma omp parallel
    {
        int thread_sum = 0;
        int thread_prefix = 0;

        #pragma omp for schedule(static)
        for(int i = 0; i < n; i++) {
            thread_sum += a[i] + b[i];
            d[i] = thread_sum;
        }

        #pragma omp single
        {
            for(int i = 1; i < n; i++)
            {
                d[i] += d[i-1];
            }
        }
    }

    printf("Sequential:\n");
    for(int i = 0; i < 6; i++)
    {
        printf("%d ", c[i]);
    }
    printf("\n");

    printf("Parallel:\n");
    for(int i = 0; i < 6; i++)
    {
        printf("%d ", d[i]);
    }
    printf("\n");

    int is = 0;
    for(int i = 0; i < 6; i++)
    {
        if(c[i] != d[i])
        {
            is = 1;
            break;
        }
    }

    if(is == 1)
        printf("\nFor sequential and parallel the results are not the same");
    else
        printf("\nFor sequential and parallel the results are the same");
}
