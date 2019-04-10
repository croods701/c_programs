#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int ask_choice(int m, int n, char *ques)
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

int binary_search(int arr[], int low, int high, int val)
{
    if (high >= low)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == val)
            return mid;
        if (arr[mid] > val)
            return binary_search(arr, low, mid - 1, val);
        return binary_search(arr, mid + 1, high, val);
    }
    return -1;
}

void input_array(int array[], int n)
{
    printf("Enter the values seprated by space: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
}

void print_array(int array[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main()
{
    int arr[MAX];
    printf("\t Welcome to Binary Search \n");
    int n = ask_choice(1, 50, "Enter the lenght of array");
    input_array(arr, n);
        printf("Array: ");
        print_array(arr, n);
        printf("\n");

    int flag = 1;
    while (flag)
    {
        int val = ask_choice(-9999, 99999, "Enter the value to search:");
        int pos = binary_search(arr, 0, n - 1, val);
        if (pos == -1)
            printf("Not Found \n");
        else
            printf("Found %d at %d \n", val, pos);
        printf("\n");
    }
}
