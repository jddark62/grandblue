#include <stdio.h>

int main()
{
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
