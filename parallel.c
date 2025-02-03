#include <stdio.h>
#include <omp.h>

int main()
{
    //omp_set_num_threads(5);

    #pragma omp parallel for
    for(int i = 1; i <= 100000; i++)
    {
        long long sum = 0;
        for(int j = 1; j <= 100000; j++)
        {
            sum += j;
        }
    }

    return 0;
}
