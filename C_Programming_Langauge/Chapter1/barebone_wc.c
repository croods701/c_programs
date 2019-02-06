#include <stdio.h>

#define TAB 9
#define NEWLINE 10
#define BLANK 32

//Part of Version2
#define IN 1
#define OUT 0

// int main()
// {
//     int tb = 0, nl = 0, bl = 0;

//     int c;
//     for (tb = 0, nl = 0, bl = 0; c != EOF; c == TAB ? ++tb : (c == NEWLINE ? ++nl : (c == BLANK ? ++bl : 0)))
//         c = getchar();

//     printf("Line: %d\tBlank: %d\tTab: %d\n", nl, bl, tb);
// }

// Version 2
int main()
{

    int nl, tb, bl, nw, nc, c, state;

    state = OUT;
    nl = tb = bl = nw = nc = 0;

    while ((c = getchar()) != EOF)
    {
        ++nc;

        if (c == NEWLINE)
            ++nl;
        if (c == TAB)
            ++tb;
        if (c == BLANK)
            ++bl;
        if (c == TAB || c == NEWLINE || c == BLANK)
            state = OUT;
        else if (state == OUT)
        {
            state = IN;
            ++nw;
        }
    }

    printf("Line: %d\tBlank: %d\tTab: %d\tChar: %d\tWords: %d\n", nl, bl, tb, nc, nw);
}