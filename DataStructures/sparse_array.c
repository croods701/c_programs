#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 50

void pause(void)
{
    fflush(stdout);
    getchar();
    getchar();
}

void clear()
{
    system("cls");
}

//orient = 0 : Horizontal
//orient = 1; Vertical
int print_2d_array(int m, int n, int arr[m][n], int upto_row)
{
    if (m <= 0 || upto_row <= 0 || n <= 0)
        return 1;
    if (upto_row > m)
        return 2;

    for (int i = 0; i < upto_row; i++)
    {

        for (int j = 0; j < n; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

int get_triplet(int m, int n, int arr[m][n], int upto_row, int upto_col, int outarr[][3])
{
    outarr[0][0] = upto_row;
    outarr[0][1] = upto_col;
    int filled = 0;
    for (int i = 0; i < upto_row; i++)
        for (int j = 0; j < upto_col; j++)
            if (arr[i][j] != 0)
            {
                filled++;
                outarr[filled][0] = i + 1;
                outarr[filled][1] = j + 1;
                outarr[filled][2] = arr[i][j];
            }

    outarr[0][2] = filled;
    return filled;
}

int _input_2d_array(int m, int n, int arr[m][n], int upto_row, int upto_col)
{
    if (m <= 0 || upto_row <= 0 || n <= 0)
        return 1;
        
    if (upto_row > m || upto_col > n)
        return 2;

    printf("Enter the matrix row by row, values in col should be seprated by SINGLE space. \n");
    for (int i = 0; i < upto_col; i++)
        printf("*   ");
    printf("\n");

    fflush(stdin);
    for (int i = 0; i < upto_row; i++)
    {
        for (int j = 0; j < upto_col; j++)
        {
            if (!((i == upto_row - 1) && (j == upto_col - 1)))
                scanf("%d ", &arr[i][j]);
        }
    }
    scanf("%d", &arr[upto_row - 1][upto_col - 1]);
    return 0;
}

void welcome()
{
    printf("\t Sparse Array To Triplet \n");
    printf("--------------------------------------- \n");

    printf("\t 1. Input Sparse Array \n");
    printf("\t 2. View Triplet \n");
    printf("\t 3. Exit \n");
}

void input_2d_array(int m, int n, int arr[m][n], int *upto_row, int *upto_col)
{
    clear();
    printf("\t Array Input \n");
    printf("--------------------------------------- \n");

    printf("Enter the no. of rows and col: ");
    scanf("%d %d", upto_row, upto_col);
    printf("\n");

    int res = _input_2d_array(m, n, arr, *upto_col, *upto_col);
    if (res == 1)
    {
        printf("[ERROR] Please enter positive indexes \n");
    }
    else if (res == 2)
    {
        printf("[ERROR] Please values less than 50.\n");
    }
    else if (res == 0)
    {
        printf("Matrix Entered. \n");
    }

    pause();
    clear();
}

void print_triplet(int m, int n, int arr[m][n], int upto_row, int upto_col, int outarr[][3])
{
    clear();
    if (!(upto_col == 0 && upto_row == 0))
    {
        printf("\tTriplet  \n");
        printf("--------------------------------------- \n");

        int filled = get_triplet(m, n, arr, upto_row, upto_col, outarr);

        if (filled <= (upto_col * upto_row) / 2)
        {
            int upto_row_t = filled + 1;
            print_2d_array(m, 3, outarr, upto_row_t);
        }
        else
        {
            printf("[ERROR] Input array is not Sparse. \n");
        }
    }
    else
    {
        printf("{ERROR]Array is EMPTY, Please input matrix first. \n");
    }

    pause();
    clear();
}

int main()
{
    clear();

    int array[50][50] = {0};
    int outarray[51][3] = {0};
    int last_row = 0;
    int last_col = 0;

    int flag = 0;

    while (flag == 0)
    {
        welcome();
        int ch;
        printf("Please Choose option : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            input_2d_array(50, 50, array, &last_row, &last_col);
            break;

        case 2:
            print_triplet(50, 50, array, last_row, last_col, outarray);
            break;

        case 3:
            flag = 1;
            break;
        default:
            break;
        }
    }

    pause();
}