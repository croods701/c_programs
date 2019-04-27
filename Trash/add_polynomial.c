#include <stdio.h>
#include <stdlib.h>
struct node
{
    int coeff;
    int pow;
    struct node *next;
};

void sortingf(struct node *c)
{
    //implements selection sort
    struct node *temp1, *temp2, *mini;
    int co, p;
    temp1 = temp2 = mini = c;
    while (temp1 != NULL)
    {
        temp2 = temp1->next;
        mini = temp1;
        while (temp2 != NULL)
        {
            if (temp2->pow < mini->pow)
                mini = temp2;
            temp2 = temp2->next;
        }
        if (mini != temp1)
        {
            co = temp1->coeff;
            p = temp1->pow;
            temp1->coeff = mini->coeff;
            temp1->pow = mini->pow;
            mini->coeff = co;
            mini->pow = p;
        }
        temp1 = temp1->next;
    }
}


struct node *create()
{
    int n, i = 0;
    struct node *t_head, *newnode, *curnode;
    printf("\nenter the total number of terms in polynomial");
    scanf("%d", &n);
    while (i < n)
    {
        i += 1;
        printf("\nenter coefficient and power ");
        newnode = (struct node *)malloc(sizeof(struct node));
        scanf("%d %d", &(newnode->coeff), &(newnode->pow));
        if (i == 1)
        {
            t_head = newnode;
            curnode = newnode;
        }
        else
        {
            curnode->next = newnode;
            curnode = newnode;
        }
    }
    curnode->next = NULL;
    sortingf(t_head);
    return t_head;
}

void display(struct node *t)
{
    struct node *temp;
    temp = t;
    printf("\n");
    while (temp != NULL)
    {
        printf("+(%d(x^%d))", temp->coeff, temp->pow);
        temp = temp->next;
    }
}
int main()
{
    struct node *head1;
    head1 = create();
    printf("\n%u",head1);
    display(head1);
    printf("\n%u",head1);
    return 0;
}
