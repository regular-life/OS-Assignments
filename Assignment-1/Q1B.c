#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void factorial(int n)
{
    int ans = 1 ;
    for (int i = 2 ; i <= n ; i ++)
    {
        ans *= i ;
    }
    printf("Factorial of %d is : %d\n", n, ans) ;
}

void fibonacci(int n)
{
    int prev = 0, curr = 1 ;
    printf("First %d fibonacci numbers are : %d %d ", n, prev, curr) ;
    for (int i = 2 ; i < n ; i ++)
    {
        int temp = curr ;
        curr += prev ;
        prev = temp ;
        printf("%d ", curr) ;
    }
    printf("\n") ;
}

signed main(int argc, char *argv[])
{
    pid_t fk = vfork() ;
    if (fk < 0)
    {
        printf("Failure. Why ?????\n") ;
    }
    else if (fk == 0)
    {
        factorial(4) ;
    }
    else
    {
        fibonacci(16) ;
    }
}