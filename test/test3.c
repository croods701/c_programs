#include <stdio.h>
#include <stdlib.h>

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
    const int MAX = 10;
    char line[MAX];
    int len = getline(line,MAX);
    
    // scanf("%s",line);
    printf("%s",line);
    int a = getchar();
    int b = getchar();
    printf("%d %d \n",a,b);
}