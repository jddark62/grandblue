#include<stdio.h>
#include<omp.h>

int main()
{
    int n = 10;
    long long sum = 0, sum1 = 0;

    omp_set_num_threads(8);
    #pragma omp parallel
    {
        for(int i = 1; i <= n; i++)
        {
            sum++;
        }
    }

    #pragma omp parallel for
    for(int i = 1; i <= n; i++)
    {
        #pragma omp critical
        sum1++;
    }

    printf("Race Condition: Sum: %lld\n", sum);
    printf("No Race Condition: Sum: %lld\n", sum1);
}
