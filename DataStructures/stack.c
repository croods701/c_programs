#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 5

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

void print_stack(int top, int arr[])
{
    clear();
    printf("\tCurrent Stack \n");

    if (top >= 0)
    {
        printf("\t ----- \n");
        for (int i = top; i >= 0; i--)
            printf("\t | %d | \n\t ----- \n", arr[i]);
    }
    else
    {
        printf("[ERROR] Array is Empty. \n");
    }

    pause();
    clear();
}

int _push(int n, int arr[], int *pos, int val)
{
    if (*pos + 1 > n - 1)
    {
        return 2;
    }
    *pos = *pos + 1;
    arr[*pos] = val;

    return 0;
}

int _pop(int n, int arr[], int *pos, int *val_pop)
{
    if (*pos < 0)
    {
        return 1;
    }

    *val_pop = arr[*pos];
    *pos = *pos - 1;
    return 0;
}

void push(int n, int arr[], int *pos)
{
    clear();
    printf("\t Push \n");
    printf("--------------------------- \n");

    printf("Enter Val : ");
    int v;
    scanf("%d", &v);
    int res = _push(n, arr, pos, v);
    if (res == 0)
    {
        printf("Sucessfully Pushed value. \n");
    }
    else if (res == 2)
    {
        printf("Overflow Occurs. \n");
    }

    pause();
    clear();
}

void pop(int n, int arr[], int *pos)
{
    clear();
    printf("\t Pop \n");
    printf("------------------------------ \n");

    int v;
    int res = _pop(n, arr, pos, &v);
    if (res == 0)
    {
        printf("Sucessfully Poped %d from stack. \n", v);
    }
    else if (res == 1)
    {
        printf("Underflow Occurs. \n");
    }

    pause();
    clear();
}

void welcome()
{
    printf("\t Stack Program \n");
    printf("-------------------------------\n");

    printf("\t 1. Push \n");
    printf("\t 2. Pop \n");
    printf("\t 3. Print \n");
    printf("\t 4. Exit \n");
}

int main()
{
    clear();

    int array[MAX_LEN] = {0};
    int top = -1;

    int flag = 0;

    while (flag == 0)
    {
        clear();
        welcome();
        int ch;
        printf("Please Choose option : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            push(MAX_LEN, array, &top);
            break;

        case 2:
            pop(MAX_LEN, array, &top);
            break;

        case 3:
            print_stack(top, array);
            break;

        case 4:
            flag = 1;
            break;
        default:
            break;
        }
    }

    pause();
}