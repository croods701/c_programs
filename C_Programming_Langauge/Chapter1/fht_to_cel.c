#include <stdio.h>
#include <math.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main()
{

    for (int fhr = LOWER; fhr <= UPPER; fhr += STEP)
    {
        printf("%3d\t%6.1f\n", fhr, (5.0 / 9.0) * (fhr - 32));
    }
}
