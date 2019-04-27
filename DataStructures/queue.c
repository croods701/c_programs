#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 5

int ARRAY[MAX_LEN];
int TOP = -1;
int BOTTOM = -1;

int queue(int val)
{
    if (TOP + 1 >= MAX_LEN)
        return -1;
    if (TOP == -1 || BOTTOM == -1)
        BOTTOM = 0;
    ARRAY[++TOP] = val;
    return 0;
}

int dequeue(int *val)
{
    if (TOP < BOTTOM)
        return -1;
    *val = ARRAY[BOTTOM++];
    return 0;
}

void print_queue()
{
    if (TOP == -1)
        return;
    for (int i = BOTTOM; i <= TOP; i++)
        printf("%d ", ARRAY[i]);
}

void welcome()
{
    printf("-------------------------------\n");
    printf("\t Queue Program \n");
    printf("-------------------------------\n");
    printf("Queue :");
    print_queue();
    printf("\n");
    printf("\t 1. Enqueue \n");
    printf("\t 2. Dequeue \n");
    printf("\t 3. Exit \n");
}

int main()
{
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
            printf("Enter the value to enqueue: ");
            int val;
            scanf("%d",&val);
            int st1 = queue(val);
            if(st1)
                printf("OVERFLOW \n");
            else
                printf("Sucefully Enqueued \n");
            break;

        case 2:;
            int val_out;
            int st2 = dequeue(&val_out);
            if(st2)
                printf("UNDERFLOW \n");
            else
                printf("Sucefully Dequeued %d \n",val_out);
            break;

        case 3:
            flag = 1;
            break;
        default:
            break;
        }
    }

}