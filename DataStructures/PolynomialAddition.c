#include <stdio.h>
#include <stdlib.h>

#define NL printf("\n")
#define SEP '-'

void draw_seprator(char sep, int len)
{
    for (int i = 0; i < len; i++)
    {
        putchar(sep);
    }
    printf("\n");
}

typedef struct node
{
    int num;
    int coeff;
    struct node *next;
} list_node;

struct node *start1 = NULL;
struct node *start2 = NULL;
struct node *start3 = NULL;

struct node *add_node(struct node *start, int n, int c)
{
    struct node *ptr, *new_node;
    if (start == NULL)
    {
        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->num = n;
        new_node->coeff = c;
        new_node->next = NULL;
        start = new_node;
    }
    else
    {
        ptr = start;
        while (ptr->next != NULL)
            ptr = ptr->next;
        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->num = n;
        new_node->coeff = c;
        new_node->next = NULL;
        ptr->next = new_node;
    }
    return start;
}

struct node *create_poly(struct node *start)
{
    struct node *new_node, *ptr;
    int n, c;
    printf("To Finish Polynomial enter -1 in 'Coefficient' \n");
    printf("Enter the Coefficient & Power : ");
    scanf("%d %d", &n, &c);
    while (n != -1)
    {
        if (start == NULL)
        {
            new_node = (struct node *)malloc(sizeof(struct node));
            new_node->num = n;
            new_node->coeff = c;
            new_node->next = NULL;
            start = new_node;
        }
        else
        {
            ptr = start;
            while (ptr->next != NULL)
                ptr = ptr->next;
            new_node = (struct node *)malloc(sizeof(struct node));
            new_node->num = n;
            new_node->coeff = c;
            new_node->next = NULL;
            ptr->next = new_node;
        }
        printf("Enter the Coefficient & Power : ");
        scanf("%d %d", &n, &c);
        if (n == -1)
            break;
    }
    return start;
}
struct node *display_poly(struct node *start)
{
    struct node *ptr;
    ptr = start;
    while (ptr->next != NULL)
    {
        printf("%dx%d  +  ", ptr->num, ptr->coeff);
        ptr = ptr->next;
    }
    printf("%dx%d \n", ptr->num, ptr->coeff);
    return start;
}
struct node *add_poly(struct node *start1, struct node *start2, struct node *start3)
{
    struct node *ptr1, *ptr2;
    int sum_num, c;
    ptr1 = start1, ptr2 = start2;
    while (ptr1 != NULL && ptr2 != NULL)
    {
        if (ptr1->coeff == ptr2->coeff)
        {
            sum_num = ptr1->num + ptr2->num;
            start3 = add_node(start3, sum_num, ptr1->coeff);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        else if (ptr1->coeff > ptr2->coeff)
        {
            start3 = add_node(start3, ptr1->num, ptr1->coeff);
            ptr1 = ptr1->next;
        }
        else if (ptr1->coeff < ptr2->coeff)
        {
            start3 = add_node(start3, ptr2->num, ptr2->coeff);
            ptr2 = ptr2->next;
        }
    }
    if (ptr1 == NULL)
        while (ptr2 != NULL)
        {
            start3 = add_node(start3, ptr2->num, ptr2->coeff);
            ptr2 = ptr2->next;
        }
    if (ptr2 == NULL)
        while (ptr1 != NULL)
        {
            start3 = add_node(start3, ptr1->num, ptr1->coeff);
            ptr1 = ptr1->next;
        }

    return start3;
}

int main()
{
    int op;
    do
    {
        draw_seprator(SEP, 40);
        printf("\t Polynomial Program \n");
        draw_seprator(SEP, 40);
        printf("1. Enter the first polynomial \n");
        printf("2. Enter the second polynomial \n");
        printf("3. Add the polynomials \n");
        printf("4. Exit \n");
        printf("Enter your option : ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            start1 = create_poly(start1);
            printf("Entered Polynomial is : ");
            display_poly(start1);
            break;
        case 2:
            start2 = create_poly(start2);
            printf("Entered Polynomial is : ");
            display_poly(start2);
            break;
        case 3:
            start3 = add_poly(start1, start2, start3);
            printf("Result is : ");
            display_poly(start3);
            break;
        }
    } while (op != 4);
    return 0;
}