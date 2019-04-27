#include <stdio.h>
#include <stdlib.h>

#define New_Mem(type) ((type *)malloc(sizeof(type)))
#define NL printf("\n")
#define SEP '-'
#define MAX_SIZE 5

//Utilities Function
int ask_choice(char *ques, int m, int n)
{
    int ch;
    printf("%s :", ques);
    scanf("%d", &ch);
    while (ch < m || ch > n)
    {
        printf("%s :", ques);
        scanf("%d", &ch);
    }
    return ch;
}

void draw_seprator(char sep, int len)
{
    for (int i = 0; i < len; i++)
    {
        putchar(sep);
    }
    printf("\n");
}

void print_array(int array[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void selection_sort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int flag = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[flag] > arr[j])
                flag = j;
        }
        if (flag != i)
        {

            int temp = arr[i];
            arr[i] = arr[flag];
            arr[flag] = temp;
        }
    }
}

int insert(int array[], int *n, int pos, int val)
{
    if (pos > *n)
        return -1;
    if (*n + 1 >= MAX_SIZE)
        return -2;
    

    if (pos == 0)
    {
        int temp = *n;
        if (*n==0)
            temp =1;

        for (int i = temp - 1; i >= 0; i--)
        {
            array[i + 1] = array[i];
        }
        array[pos] = val;
        
    }
    else if (pos == *n)
    {
        array[pos] = val;
    }
    else
    {
        for (int i = (*n) - 1; i >= pos; i--)
        {
            array[i + 1] = array[i];
        }
        array[pos] = val;
    }

    
    (*n)++;
    return 0;
}

int delete (int array[], int *n, int pos)
{
    if (pos > *n)
        return -1;
    if (*n <= 0)
        return -2;
    for (int i = pos; i < *n - 2; i++)
    {
        array[i] = array[i + 1];
    }
    (*n)--;
    return 0;
}

int search(int array[], int n, int val)
{
    for (int i = 0; i < n; i++)
        if (array[i] == val)
            return i;
    return -1;
}

void welcome(int array[], int n)
{
    draw_seprator(SEP, 40);
    printf("\t Welcome to Array Modification \n");
    draw_seprator(SEP, 40);
    printf("Array: ");
    print_array(array, n);

    printf("Insert- \n");
    printf(" 1. Begining\t2. End\t 3. Specific Position \n");
    printf("Deletion- \n");
    printf(" 4. Begining\t5. End\t 6. Specific Position \n");
    printf("7. Search \n");
    printf("8. Sort \n");
    printf("9. Exit \n");
}

int main()
{
    int arr[MAX_SIZE] = {0};
    int size = 0;
    int sz;
    int flag = 1;
    while (flag)
    {
        welcome(arr, size);
        int ch = ask_choice("Enter Choice", 1, 9);
        switch (ch)
        {
        case 1:;
            int val1 = ask_choice("Enter the value", -9999, 9999);
            int st1 = insert(arr, &size, 0, val1);
            if (st1 == -2)
                printf("Overflow \n");
            break;
        case 2:;
            if (size == 0)
                sz = 1;
            int val2 = ask_choice("Enter the value", -9999, 9999);
            int st2 = insert(arr, &size, sz, val2);
            if (st2 == -2)
                printf("Overflow \n");
            break;
        case 3:;
            int pos1 = ask_choice("Enter the position", 0, size - 1);
            int val3 = ask_choice("Enter the value", -9999, 9999);
            int st3 = insert(arr, &size, 0, val3);
            if (st3 == -2)
                printf("Overflow \n");
            break;
        case 4:;
            int st4 = delete (arr, &size, 0);
            if (st4 == -2)
                printf("Underflow \n");
            break;
        case 5:;
            int st5 = delete (arr, &size, size - 1);
            if (st5 == -2)
                printf("Underflow \n");
            break;
        case 6:;
            int pos2 = ask_choice("Enter the position", 0, size - 1);
            int st6 = delete (arr, &size, pos2);
            if (st6 == -2)
                printf("Underflow \n");
            break;

        default:
            break;
        }
    }
}