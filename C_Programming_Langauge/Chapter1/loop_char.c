#include <stdio.h>

int main()
{

    char i;

    for (i = 0; i < 128; ++i)
    {
        printf("This is %d\n", i);

        for (int j = 0; j < 1000000; j++);
            for (int k = 0; k < 1000000; k++);
                for (int m =0; m < 1000000; m++);
                    for (int n = 0; n < 1000000; n++);
                        for (int l = 0; l < 1000000; l++);
    }
    return 0;
    }