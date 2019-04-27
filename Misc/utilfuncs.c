#include <stdlib.h>
#include <stdio.h>

#define NewLine() printf("\n")

char arand_lower()
{
    return rand() % 26 + 'a';
}

int getline(char s[], int max)
{
    int c, i;
    for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;  
}


int main()
{
    // int i;
    // char nxt, curr = arand_lower();

    // while ((curr = arand_lower()) != (nxt = arand_lower()))
    // {
    //     i++;
    //     printf("%curr", curr);
    // }
    // // printf("%c", nxt);

    
}
    