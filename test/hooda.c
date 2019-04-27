#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void selectionSort(int arr[], int);
int *copyOfArray(int arr[], int);
void heapSort(int arr[], int);
void heapify(int arr[], int, int);
void insertionSort(int arr[], int);
void mergeSort(int arr[], int);
void merge(int arr[], int left[], int, int right[], int);
void bubbleSort(int arr[], int);
int partition(int arr[], int, int);
void quickSort(int arr[], int, int);

int main()
{
    const int MAXSIZE = 50;
    int A[MAXSIZE];
    int numOfEle;
    printf("****************************************\n");
    printf("\tWelcome To Sorting Program:\n");
    printf("****************************************\n");
    printf("Enter the number of elements you want to sort\n ");
    scanf(" %d", &numOfEle);
    printf("Enter the unsorted list::\n");

    for (int i = 0; i < numOfEle; ++i)
        scanf("%d", &A[i]);
    int *ptr = copyOfArray(A, numOfEle);
    bool exit = false;
    while (!exit)
    {
        int opt;
        printf("Select The correct option\n");
        printf("1.Selection Sort\n2.Heap Sort\n3.Insertion Sort\n4.Merge Sort\n5.Bubble Sort\n6.Quick Sort\n7.Shell Sort\n8.Exit\n");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            selectionSort(ptr, numOfEle);
            break;
        case 2:
            heapSort(ptr, numOfEle);
            break;
        case 3:
            insertionSort(ptr, numOfEle);
            break;
        case 4:
        {
            mergeSort(ptr, numOfEle - 1);
            for (int i = 0; i < numOfEle; i++)
                printf("%d\t", ptr[i]);
            printf("\n");
        }
        break;
        case 5:
            bubbleSort(ptr, numOfEle);
            break;
        case 6:
        {
            quickSort(ptr, 0, numOfEle - 1);
            for (int i = 0; i < numOfEle; i++)
                printf("%d\t", ptr[i]);
            printf("\n");
        }
        break;
        case 7:
            break;
        case 8:
            exit = true;
            break;
        default:
            printf("Invalid Input \nTry Again:\n");
            break;
        }
    }
}
void selectionSort(int arr[], int size)
{
    printf("This is selection sort\n");
    printf("**************************\n");
    for (int i = 0; i < size; ++i)
        printf("%d\t", arr[i]);
    printf("\n");
    //selection sort algorithm
    for (int i = 0; i < size - 1; i++)
    {
        int check = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[check] > arr[j])
                check = j;
        }
        if (check != i)
        {

            int temp = arr[i];
            arr[i] = arr[check];
            arr[check] = temp;
        }
    }
    /* end*/
    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    printf("\n");
}
int *copyOfArray(int arr[], int size)
{
    int *newArray;
    newArray = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i)
        newArray[i] = arr[i];
    return newArray;
}
void heapSort(int arr[], int size)
{
    printf("Given Array:\n");
    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    printf("\n");

    for (int i = (size / 2 - 1); i >= 0; i--)
        heapify(arr, size, i);
    for (int i = size - 1; i >= 0; i--)
    {
        int swap;
        swap = arr[0];
        arr[0] = arr[i];
        arr[i] = swap;
        heapify(arr, i, 0);
    }
    printf("New Sorted Array is:\n");
    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    printf("\n");
}
void heapify(int arr[], int size, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && arr[l] > arr[largest])
        largest = l;
    if (r < size && arr[r] > arr[largest])
        largest = r;
    if (largest != i)
    {
        int swap;
        swap = arr[largest];
        arr[largest] = arr[i];
        arr[i] = swap;
        heapify(arr, size, largest);
    }
}
void insertionSort(int arr[], int size)

{
    printf("Given Array:\n");
    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    printf("\n");

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
    printf("New Sorted Array is:\n");
    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    printf("\n");
}
void mergeSort(int arr[], int size)
{
    if (size < 2)
        return;
    int mid = size / 2;
    int *left = (int *)malloc(sizeof(int) * mid);
    int *right = (int *)malloc(sizeof(int) * (size - mid));
    for (int i = 0; i <= mid - 1; i++)
        left[i] = arr[i];
    for (int i = mid; i <= size - 1; i++)
        right[i] = arr[size - mid];
    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(arr, left, mid, right, size - mid);
    free(left);
    free(right);
}
void merge(int arr[], int left[], int leftCount, int right[], int rightCount)
{
    int i = 0, j = 0, k = 0;
    while (i < leftCount && j < rightCount)
    {
        if (left[i] < right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < leftCount)
        arr[k++] = left[i++];
    while (j < rightCount)
        arr[k++] = right[j++];
}
void bubbleSort(int arr[], int size)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i <= size - 2; i++)
        {

            if (arr[i] > arr[i + 1])
            {
                int swap;
                swap = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = swap;
                sorted = false;
            }
        }
    }
    printf("New Sorted list:\n");
    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    printf("\n");
}

void quickSort(int arr[], int start, int end)
{
    if (start < end)
    {
        int pIndex = partition(arr, start, end);
        quickSort(arr, start, pIndex - 1);
        quickSort(arr, pIndex + 1, end);
    }
}
int partition(int arr[], int start, int last)
{
    int pivot = arr[last];
    int pIndex = start;
    for (int i = start; i < last; i++)
    {
        if (arr[i] <= pivot)
        {
            int swap = arr[i];
            arr[i] = arr[pIndex];
            arr[pIndex] = swap;
            pIndex++;
        }
    }
    int swap = arr[last];
    arr[last] = arr[pIndex];
    arr[pIndex] = swap;

    return pIndex;
}
