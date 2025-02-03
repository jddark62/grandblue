#include <stdio.h>
#include <omp.h>

int main()
{
    int n = 9999999;
    long long sum = 0;

    //printf("Enter n: ");
    //scanf("%d", &n);

    omp_set_num_threads(5);
    #pragma omp parallel for
    for(int i = 1; i <= n; i++)
    {
        #pragma omp critical
        {
            sum += i;
        }
    }

    printf("Sum of first %d natural numbers: %lld\n", n, sum);
}
