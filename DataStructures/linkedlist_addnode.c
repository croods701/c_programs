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

void welcome(linkedlist *list)
{
    draw_seprator(SEP, 40);
    printf("\t Welcome to Merge LinkedList Program \n");
    draw_seprator(SEP, 40);

    printf("Merged List : ");
    display_linkedlist(list);
    printf("\n");

    printf("1. Add Node at Beginning \n");
    printf("2. Add Node at End \n");
    printf("3. Add Node at Specific position \n");
    printf("4. Exit \n");
}

void linkedlist_add_operations()
{
    linkedlist *list = new_linear_list();
    int flag = 0;
    while (flag == 0)
    {
        welcome(list);
        int ch = ask_choice(1, 6, "Select any option");
        switch (ch)
        {
        case 1:
            add_node(list, 1, ask_choice(-99999, 99999, "Enter the value you want to add"));
            break;

        case 2:
            add_node(list, list->size + 1, ask_choice(-99999, 99999, "Enter the value you want to add"));
            break;

        case 3:;
            int val = ask_choice(1, list->size + 1, "Enter the postion");
            int status = add_node(list, val, ask_choice(-99999, 99999, "Enter the value you want to add"));
            if (status == -1)
                printf("[ERROR] OverFlow. \n");
            else if (status == -2)
                printf("[ERROR] UnderFlow. \n");
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
    linkedlist_add_operations();
}