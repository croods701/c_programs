#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define NL printf("\n")
#define New_Mem(type, n) ((type *)malloc(sizeof(type) * n))
#define SEP '-'

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

void draw_seprator(char sep, int len)
{
    for (int i = 0; i < len; i++)
    {
        putchar(sep);
    }
    printf("\n");
}

void copy_array(int to[], int from[], int size)
{
    memcpy(to, from, sizeof(from) * size);
}
void clear_array(int arr[], int size)
{
    memset(arr, 0, size * sizeof(int));
}

void print_array(int array[], int size)
{
    if (!array)
    {
        printf("Array is Empty \n");
        return;
    }
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    NL;
}

void quick_sort(int arr[], int start, int end)
{
    if (start < end)
    {
        int index = partition(arr, start, end);
        quick_sort(arr, start, index - 1);
        quick_sort(arr, index + 1, end);
    }
}
int partition(int arr[], int start, int last)
{
    int pivot = arr[last];
    int index = start;
    for (int i = start; i < last; i++)
    {
        if (arr[i] <= pivot)
        {
            int temp = arr[i];
            arr[i] = arr[index];
            arr[index] = temp;
            index++;
        }
    }
    int temp = arr[last];
    arr[last] = arr[index];
    arr[index] = temp;
    return index;
}

void heap_sort(int arr[], int size)
{
    for (int i = (size / 2 - 1); i >= 0; i--)
        heapify(arr, size, i);
    for (int i = size - 1; i >= 0; i--)
    {
        int temp;
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}
void heapify(int arr[], int size, int i)
{
    int biggest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && arr[l] > arr[biggest])
        biggest = l;
    if (r < size && arr[r] > arr[biggest])
        biggest = r;
    if (biggest != i)
    {
        int temp;
        temp = arr[biggest];
        arr[biggest] = arr[i];
        arr[i] = temp;
        heapify(arr, size, biggest);
    }
}

void insertion_sort(int arr[], int size)
{
    for (int i = 1; i <= size; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
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

void bubble_sort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void merge(int arr[], int l, int mid, int r)
{
    int i, j, k;
    int num1 = mid - l + 1;
    int num2 = r - mid;

    int left[num1], right[num2];

    for (i = 0; i < num1; i++)
        left[i] = arr[l + i];
    for (j = 0; j < num2; j++)
        right[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < num1 && j < num2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < num1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < num2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        merge_sort(arr, l, mid);
        merge_sort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

void shell_sort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

void print_welcome_message(int a[], int size)
{
    draw_seprator(SEP,40);
    printf("\t Welcome to Sorting Program\n");
    draw_seprator(SEP,40);

    printf("Array: ");
    print_array(a, size);

    printf("1. Enter Array \n");
    printf("2. Bubble Sort \n");
    printf("3. Insertion Sort \n");
    printf("4. Selection Sort \n");
    printf("5. Merge Sort \n");
    printf("6. Shell Sort \n");
    printf("7. Heap Sort \n");
    printf("8. Exit \n");
}

void array_input(int *arr, int *size)
{
    *size = ask_choice(1, 999, "Enetr length of array");
    printf("Enter the elements seprated by space: ");
    for (int i = 0; i < *size; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void sort_prgm()
{
    int *my_array = NULL;
    int temp_arr[100] = {0};
    int size = 0;
    int flag = 1;

    while (flag)
    {
        print_welcome_message(my_array, size);
        int ch = ask_choice(1, 8, "Enter your Choice");

        switch (ch)
        {
        case 1:
            if (!my_array)
                my_array = New_Mem(int, 100);
            array_input(my_array, &size);
            break;

        case 2:
            if (my_array)
            {
                copy_array(temp_arr, my_array, size);
                bubble_sort(temp_arr, size);
                printf("Bubble Sorted Array is : ");
                print_array(temp_arr,size);
            }
            break;
        case 3:
            if (my_array)
            {
                copy_array(temp_arr, my_array, size);
                insertion_sort(temp_arr, size);
                printf("Insertion Sorted Array is : ");
                print_array(temp_arr,size);
            }
            break;
        case 4:
            if (my_array)
            {
                copy_array(temp_arr, my_array, size);
                selection_sort(temp_arr, size);
                printf("Selection Sorted Array is : ");
                print_array(temp_arr,size);
            }
            break;
        case 5:
            if (my_array)
            {
                copy_array(temp_arr, my_array, size);
                merge_sort(temp_arr, 0,size-1);
                printf("Merge Sorted Array is : ");
                print_array(temp_arr,size);
            }
            break;
        case 6:
            if (my_array)
            {
                copy_array(temp_arr, my_array, size);
                shell_sort(temp_arr, size);
                printf("Shell Sorted Array is : ");
                print_array(temp_arr,size);
            }
            break;
        case 7:
            if (my_array)
            {
                copy_array(temp_arr, my_array, size);
                heap_sort(temp_arr, size);
                printf("Heap Sorted Array is : ");
                print_array(temp_arr,size);
            }
            break;
        case 8:
            flag = 0;
            break;

        default:
            break;
        }
    }
}

int main()
{
    sort_prgm();
}