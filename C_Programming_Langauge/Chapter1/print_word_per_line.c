#include <stdio.h>

#define BLANK 32
#define NEWLINE 10

int main()
{

    int c;
    while ((c = getchar()) != EOF)
        c == 32 ? putchar(NEWLINE) : putchar(c);
}
