#include <stdio.h>
#include <stdlib.h>

char *reverse(char *);

void main()
{
    printf("%d\n", sizeof(5));
    int *ptr;
    ptr = &5;
    

    // printf("%s", reverse("Computer"));
    // //return 0;

    // getchar();
}
char *reverse(char *p)
{
    int i, l;
    char ch;
    for (l = 0; *(p + l) != '\0'; l++)
        ;
    for (i = 0; i < (l / 2); i++)
    {
        ch = *(p + i);
        int offset = l - 1 - i;
        *(p + i) = *(p + offset);
        *(p + offset) = ch;
        printf("\n");
    }
    return (p);
}