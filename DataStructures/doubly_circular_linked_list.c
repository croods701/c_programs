#include<stdio.h>
//typedef struct node;
typedef struct node
{
    int info;
    struct node *next;
    struct node* prev;
} node;
//typedef struct node;
node *head;

int input(const char *a)
{
    printf("\n");
    printf(a);
    printf("\n");
    int d;
    scanf("%d",&d);
    return d;
}
void disp(node*head1)
{
    if(head==NULL)
    {
        printf("Empty\n");
        return;
    }
    printf("starting address %p\n",head1);
    do
    {
        printf("%d,",head1->info);
        head1=head1->next;
    }
    while(head1!=head);
    printf("\b \n");
    printf("ending address %p\n\n",head1);
}
void create_node(node *head1)
{
    printf("Enter data:");
    scanf("%d",&(head1->info));
    printf("\nEnter more(y/n)");
    char c;
    scanf("%*c%c",&c);
    if(c=='y')
    {
        head1->next=(node*)malloc(sizeof(node));
        head1->next->prev=head1;
        create_node(head1->next);
    }
    else
    {
        head->prev=head1;
        head1->next=head;
    }
}
void insert(node *head1)
{
    if(head==NULL)
    {
        head=(node*)malloc(sizeof(node));;
        create_node(head);
        disp(head);
        return;
    }
    int d=input("1:beg\n2:end\n3:loc");
    node *head2=(node*)malloc(sizeof(node));
    head2->info=input("Enter data");


    switch(d)
    {
    case 1:
    {
        head2->next=head1;
        head2->prev=head1->prev;
        head1->prev=head2;
        head2->prev->next=head2;
        head=head2;
        break;
    }
    case 2:
    {
        head2->next=head1;
        head2->prev=head1->prev;
        head1->prev=head2;
        head2->prev->next=head2;
        break;

    }
    case 3:
    {
        int loc=input("Enter the element after which the link is to be inserted");
        while(head1->info!=loc)
            head1=head1->next;
        head2->next=head1->next;
        head2->prev=head1;
        head2->next->prev=head2;
        head1->next=head2;
        break;
    }
    }
    disp(head);

}
void del(node *head1)
{
    if(head==NULL)
    {
        printf("Underflow");
        return;
    }
    if(head1->next==head1)
    {
        head=NULL;
        free(head1);
        disp(head);
        return;
    }
    int d=input("1:beg\n2:end\n3:loc");
    switch(d)
    {
    case 1:
    {

        head1->prev->next=head1->next;
        head1->next->prev=head1->prev;
        head=head1->next;
        free(head1);
        break;
    }
    case 2:
    {
        node*head2=head1->prev;
        head2->prev->next=head2->next;
        head2->next->prev=head2->prev;
        free(head2);
        break;
    }
    case 3:
    {
        int loc=input("Enter the element to be deleted");
        do
        {
            if(head1->info==loc)break;
            head1=head1->next;
        }
        while(head1!=head);
        if(head1==head && head1->info!=loc)
        {
            printf("location not found\n");
            return;
        }
        node*head2=head1;
        head2->prev->next=head2->next;
        head2->next->prev=head2->prev;
        if(head2==head)
            head=head2->next;
        free(head2);
        break;
    }
    }
    disp(head);
}

int main()
{
    //printf("creating head");
    head=(node*)malloc(sizeof(node));
    create_node(head);
    disp(head);
    while(1)
    {
        int d=input("1.insert\n2.delete\n3.show\n4.exit");
        switch(d)
        {
        case 1:
        {
            insert(head);
            break;
        }
        case 2:
        {
            del(head);
            break;
        }
        case 3:
        {
            disp(head);
            break;
        }
        case 4:
        {
            return 0;
            break;
        }
        }
    }
    return 0;
}
