#include <stdio.h>
#include <math.h>

int main()
{
    double c = 0;
    for (double i = 0; i < pow(2, 32); i++)
    {
        c++;
    }
    printf("Process1 %lf\n", c);
    return 0;
}
