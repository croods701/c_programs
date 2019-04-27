#include <stdio.h>

void add(int a, int b)
{
    printf("Result is - %d \n", a + b);
}

int main()
{
    while (1)
    {
        printf("Enter Two Numbers - ");
        int a, b;
        scanf("%d %d", &a, &b);
        add(a, b);
    }
}
    