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

int del_node(linkedlist *list, int pos)
{
    node *temp_head = list->head;
    //Overflow
    if (list->size < pos)
        return -1;
    if (pos <= 0)
        return -2;

    if (temp_head->next == NULL)
    {
        free(temp_head);
        list->head = NULL;
        (list->size)--;
        return 0;
    }
    if (pos == 1)
    {
        node *pos_node = get_node_by_pos(list, pos);
        list->head = pos_node->next;
        free(pos_node);
    }
    else
    {
        node *prev_node = get_node_by_pos(list, pos - 1);
        node *pos_node = get_node_by_pos(list, pos);
        prev_node->next = pos_node->next;
        free(pos_node);
    }

    (list->size)--;
    return 0;
}

void display_linkedlist(linkedlist *list)
{
    node *temp = list->head;
    while (temp != NULL)
    {
        printf("|%d|%p|    ", temp->data, temp);
        temp = temp->next;
    }
}

void push(int val, linkedlist *list)
{
    if (list->size == 0)
        add_node(list, 1, val);
    else
        add_node(list, list->size+1, val);
}

node pop(linkedlist *list)
{
    node pop_node = *get_node_by_pos(list, list->size);
    del_node(list, list->size);
    return pop_node;
}

void enqueue(int val, linkedlist *list)
{
    add_node(list, list->size + 1, val);
}

node dequeue(linkedlist *list)
{
    node pop_node = *get_node_by_pos(list, 1);
    del_node(list, 1);
    return pop_node;
}

void welcome(linkedlist *list)
{
    draw_seprator(SEP, 40);
    printf("\t Welcome to Stacks & Queues using Linked List \n");
    draw_seprator(SEP, 40);
    printf("List -");
    display_linkedlist(list);
    NL;
    printf("1. Push \n");
    printf("2. Pop \n");
    printf("3. Enqueue \n");
    printf("4. Dequeue \n");
    printf("5. Exit \n");
}

int main()
{
    linkedlist *list = new_linear_list();
    int flag = 1;
    while (flag)
    {
        welcome(list);
        int ch = ask_choice(1, 5, "Enter Choice");
        switch (ch)
        {
        case 1:
            push(ask_choice(-99999, 99999, "Enter the value to Push"), list);
            break;
        case 2:
            printf("%d is Poped from list. \n", pop(list).data);
            break;
        case 3:
            enqueue(ask_choice(-99999, 99999, "Enter the value to Enqueue"), list);
            break;
        case 4:
            printf("%d is Dequeued from list. \n", dequeue(list).data);
            break;

        case 5:
            flag = 0;
            break;

        default:
            break;
        }
    }
}