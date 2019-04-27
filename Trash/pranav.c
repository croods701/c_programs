#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    int exp;
    struct node *next;
} *head1 = NULL, *temp = NULL, *head2 = NULL, *prev, *temp2 = NULL, *prev2, **start = NULL, *head;

int main()
{
    void firstpoly();
    void secondpoly();
    void add();
    void display();
    firstpoly();
    secondpoly();
    add();
    display();
}

void firstpoly()
{
    system("cls");
    printf("ENTER THE FIRST POLYNOMIAL"); //first polynomial
    int ch;
    int num, e;
    head1 = (struct node *)malloc(sizeof(struct node));
    printf("\nEnter value to node : ");
    scanf("%d", &num);
    head1->data = num;

    printf("\nEnter exponent of the node : ");
    scanf("%d", &e);
    head1->exp = e;
    head1->next = NULL;
    prev = head1;
    printf("Added!\n");
    printf("\n\nENTER MORE NODES ?");
    printf("\n1.YES");
    printf("\n2.NO");
    printf("\nENTER CHOICE : ");
    scanf("%d", &ch);
    while (ch == 1)
    {
        temp = (struct node *)malloc(sizeof(struct node));
        printf("\nEnter value to node : ");
        scanf("%d", &num);
        temp->data = num;
        printf("\nEnter exponent of the node : ");
        scanf("%d", &e);
        temp->exp = e;
        temp->next = NULL;
        prev->next = temp;
        prev = temp;

        printf("\n\nENTER MORE NODES ?");
        printf("\n1.YES");
        printf("\n2.NO");
        printf("\nENTER CHOICE : ");
        scanf("%d", &ch);
    }
}

void secondpoly()
{
    int num2, ch2, e2;
    system("cls");
    printf("ENTER THE SECOND POLYNOMIAL"); //second polynomial
    head2 = (struct node *)malloc(sizeof(struct node));
    printf("\nEnter value to node : ");
    scanf("%d", &num2);
    head2->data = num2;
    head2->next = NULL;

    printf("\nEnter exponent of the node : ");
    scanf("%d", &e2);
    head2->exp = e2;
    prev2 = head2;
    printf("Added!\n");
    printf("\n\nENTER MORE NODES ?");
    printf("\n1.YES");
    printf("\n2.NO");
    printf("\nENTER CHOICE : ");
    scanf("%d", &ch2);
    while (ch2 == 1)
    {
        temp2 = (struct node *)malloc(sizeof(struct node));
        printf("\nEnter value to node : ");
        scanf("%d", &num2);
        temp2->data = num2;
        printf("\nEnter exponent of the node : ");
        scanf("%d", &e2);
        temp2->exp = e2;
        temp2->next = NULL;
        prev2->next = temp2;
        prev2 = temp2;

        printf("\n\nENTER MORE NODES ?");
        printf("\n1.YES");
        printf("\n2.NO");
        printf("\nENTER CHOICE : ");
        scanf("%d", &ch2);
    }
}

void add()
{
    struct node *ptr1,*ptr2, *start1;
    ptr1 = head1;
    ptr2 = head2;
    start1=*start;

    start1 = (struct node *)malloc(sizeof(struct node));
    while (ptr1 != NULL && ptr2 != NULL)
    {
        if (ptr1->exp > ptr2->exp)
        {
            start1->exp = ptr1->exp;
            start1->data = ptr1->data;
            ptr1 = ptr1->next;
        }

        else if (ptr1->exp < ptr2->exp)
        {
            start1->exp = ptr2->exp;
            start1->data = ptr2->data;
            ptr2 = ptr2->next;
        }

        else if (ptr1->exp = ptr2->exp)
        {
            start1->exp = ptr1->exp;
            start1->data = ((ptr1->data) + (ptr2->data));
            start1->next=NULL;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        // Dynamically create new node
        start1->next = (struct node *)malloc(sizeof(struct node));
        start1 = start1->next;
        start1->next = NULL;
    }
    while (ptr1 || ptr2)
    {
        if (ptr1->next)
        {
            start1->exp = ptr1->exp;
            start1->data = ptr1->data;
            ptr1 = ptr1->next;
        }
        if (ptr2->next)
        {
            start1->exp = ptr2->exp;
            start1->data = ptr2->data;
            ptr2 = ptr2->next;
        }
        start1->next = (struct node *)malloc(sizeof(struct node));
        start1 = start1->next;
        start1->next = NULL;
    }

    printf("OKAY");
}

void display()
{
    head = start;
    while (head != NULL)
    {
        printf("%d ^ %d", head->data, head->exp);
        head = head->next;
        printf("\t");
    };
}
