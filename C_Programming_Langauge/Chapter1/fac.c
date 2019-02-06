#include <stdio.h>

double fac(double num)
{
    //printf("I call myself\n");
    return (num == 0) ? 1 : num * fac(num - 1);
}

int main()
{
    double n;
    printf("Enter No - ");
    scanf("%lf", &n);
    printf("Factorial of %lf is %lf\n", n, fac(n));
}
