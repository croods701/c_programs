#include <stdlib.h>
#include <stdio.h>

#define NL printf("\n")
#define New_Mem(type) ((type *)malloc(sizeof(type)))
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

typedef struct node
{
    struct node *next;
    int data;
} node;

typedef struct linkedlist
{
    node *head;
    int size;
} linkedlist;

linkedlist *new_linear_list()
{
    linkedlist *list = New_Mem(linkedlist);
    list->size = 0;
    list->head = NULL;
    return list;
}

node *create_node(int val, node *next)
{
    node *my_node = New_Mem(node);
    my_node->data = val;
    my_node->next = next;
    return my_node;
}

//Starts 1,2,3....,size.
node *get_node_by_pos(linkedlist *list, int pos)
{
    if (list->size < pos || pos <= 0)
        return NULL;
    node *temp_node = list->head;
    for (int i = 1; i++ < pos && temp_node != NULL;)
    {
        temp_node = temp_node->next;
    }
    return temp_node;
}

node *get_node_by_val(linkedlist *list, int val)
{
    node *temp_node = list->head;
    while (temp_node != NULL)
    {
        if (temp_node->data == val)
            return temp_node;
        temp_node = temp_node->next;
    }
    return NULL;
}

int add_node(linkedlist *list, int pos, int val)
{
    node *temp_head = list->head;
    if (list->size + 1 < pos)
        return -1;
    if (pos <= 0)
        return -2;

    if (temp_head == NULL)
    {
        list->head = create_node(val, NULL);
        (list->size)++;
        return 0;
    }
    if (pos == 1)
    {
        node *prev_node = get_node_by_pos(list, pos);
        list->head = create_node(val, prev_node);
    }
    else
    {
        node *prev_node = get_node_by_pos(list, pos - 1);
        node *new_node = create_node(val, prev_node->next);
        prev_node->next = new_node;
    }
    (list->size)++;
    return 0;
}

void display_linkedlist(linkedlist *list)
{
    node *temp = list->head;
    if (!temp)
        return;
    while (temp->next != NULL)
    {
        printf("|%d|%p|--->", temp->data, temp);
        temp = temp->next;
    }
    printf("|%d|%p|", temp->data, temp);
}

linkedlist *reverse_linkedlist(linkedlist *list)
{
    node *current = list->head;
    node *prev = NULL, *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
    return list;
}

void input_linkedlist(linkedlist *list)
{
    int n = ask_choice(1, 99999, "Enter total nodes");
    printf("Enter the values seprated by space :");
    for (int i = 1; i <= n; i++)
    {
        int val;
        scanf("%d", &val);
        add_node(list, i, val);
    }
    fflush(stdin);
    fflush(stdin);
}

void welcome()
{
    printf("Welcome to LinkedList Program");
}

void linkedlist_operations_welcome(linkedlist *list)
{
    draw_seprator(SEP, 40);
    printf("\t Welcome to LinkedList Program \n");
    draw_seprator(SEP, 40);

    printf("Current List : ");
    display_linkedlist(list);
    printf("\n");

    printf("1. Input List \n");
    printf("2. Reverse\n");
    printf("3. No. of Nodes \n");
    printf("4. Exit \n");
}

void linkedlist_operations()
{
    linkedlist *list = new_linear_list();
    int flag = 0;
    while (flag == 0)
    {
        linkedlist_operations_welcome(list);
        int ch = ask_choice(1, 4, "Select any option");
        switch (ch)
        {
        case 1:
            input_linkedlist(list);
            break;

        case 2:
            reverse_linkedlist(list);
            break;

        case 3:
            printf("Total Nodes = %d \n", list->size);
            break;

        case 4:
            flag = 1;
            break;

        default:
            break;
        }
    }
}

int main()
{
    linkedlist_operations();
}