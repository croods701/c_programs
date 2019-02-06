#include <stdio.h>

int main()
{

    int c;
    int ndigit[10];

    for (int i = 0; i < 10; ++i)
        ndigit[i] = 0;

    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigit[c - '0'];

    for (int i = 0; i < 10; ++i)
        printf("%3d\t", i);

    printf("\n---------------------------------------\n");

    for (int i = 0; i < 10; ++i)
        printf("%3d\t", ndigit[i]);
    printf("\n");
}


