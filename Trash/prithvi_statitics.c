#include <stdio.h>

//creates the frequency table
void create(float ary[][3], int r)
{
    printf("enter lb ub f\n");
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &ary[i][j]);
        }
    }
}

//determines maximum frequency
//returns the row index of the lower bound of max frequency
int maxfrequency(float ary[][3], int r)
{
    int max, lb = 0;
    max = ary[lb][2]; //assumes first class has maximum frequency
    for (int i = 1; i < r; i++)
    {
        if (ary[i][2] > max) //if a class has frequency greater than current frequncy set that
        {                    //frequency as maximum frequency
            max = ary[i][2];
            lb = i;
        }
    }
    return lb;
}

//calculates cummulative frequency less than upto a cretain class
int cummulativefrequency(float ary[][3], int r)
{
    int mf = maxfrequency(ary, r);
    int cf = 0;
    for (int i = 0; i < mf; i++)
    {
        cf += ary[i][2];
    }
    return cf;
}

//calculates the total frequency of the table
int totalfrequency(float ary[][3], int r)
{
    int tf = 0;
    for (int i = 0; i < r; i++)
    {
        tf += (int)ary[i][2];
    }
    return tf;
}

//calculates the mean of frequency table
int mean(float ary[][3], int r)
{
    int f, tf = totalfrequency(ary, r);
    float x, p, sigma = 0, me, lb, ub;
    for (int i = 0; i < r; i++)
    {
        lb = ary[i][0];
        ub = ary[i][1];
        f = (int)ary[i][2];
        x = (lb + ub) / 2;
        p = f * x;
        sigma += p;
    }
    me = sigma / tf;
    return me;
}

//calculates median
float median(float ary[][3], int r)
{
    //median=l+(0.5*n-cf)*h/f

    int lbi = maxfrequency(ary, r);
    int n = totalfrequency(ary, r);
    int cf = cummulativefrequency(ary, r);
    float l = ary[lbi][0];
    int f = ary[lbi][2];
    float h = ary[lbi + 1][0] - ary[lbi][0]; //assuming class width to be of equal size
    float med = l + (0.5 * n - cf) * h / f;
    return med;
}

//calculates mode by formula mode=3median-2mean
float modef1(int median, int mean)
{
    float md = 3 * median - 2 * mean;
    return md;
}

//calculates mode by the second formula mode=l+(delta1/delta1+delta2)*h
float modef2(float ary[][3], int r)
{
    int lbi, f, f1, f2;
    float l, h, md;
    lbi = maxfrequency(ary, r);
    l = ary[lbi][0];
    f = ary[lbi][2];
    f1 = ary[lbi - 1][2];
    f2 = ary[lbi + 1][2];
    h = ary[lbi + 1][0] - ary[lbi][0];
    md = l + (f - f1) * h / (2 * f - (f1 + f2));
    return md;
}

//main
int main()
{
    int rows;
    float average, medval, modval;
    printf("enter the number of rows");
    scanf("%d", &rows);
    float ftable[rows][3];
    create(ftable, rows);
    average = mean(ftable, rows);
    printf("\n\naverage=%.2f", average);
    medval = median(ftable, rows);
    printf("\nmedian=%.2f", medval);
    modval = modef1(medval, average);
    printf("mode from formula 1=%.2f", modval);
    modval = modef2(ftable, rows);
    printf("mode from formula 2=%.2f", modval);
    return 0;
}
