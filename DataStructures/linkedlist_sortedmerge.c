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



void clear_linkedlist(linkedlist *list)
{

    list->head = NULL;
}

void display_linkedlist(linkedlist *list)
{
    node *temp = list->head;
    if(!temp)
        return;
    while (temp->next != NULL)
    {
        printf("|%d|%p|--->", temp->data,temp);
        temp = temp->next;
    }
    printf("|%d|%p|", temp->data,temp);
}

linkedlist *selection_sort_linkedlist(linkedlist *list)
{
    node *i, *j;
    int temp;
    for (i = list->head; i->next != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->data > j->data)
            {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    return list;
}


linkedlist *merge_linkedlist_sorted(linkedlist *list1, linkedlist *list2)
{
    linkedlist *result = new_linear_list();

    while (1)
    {
        if (list1->head == NULL)
        {
            get_node_by_pos(result, result->size)->next = list2->head;
            result->size += list2->size;
            break;
        }
        else if (list2->head == NULL)
        {
            get_node_by_pos(result, result->size)->next = list1->head;
            result->size += list1->size;
            break;
        }
        if (list1->head->data <= list2->head->data)
        {
            if (result->size == 0)
                add_node(result, 1, list1->head->data);
            else
                add_node(result, result->size + 1, list1->head->data);

            del_node(list1, 1);
        }
        else
        {
            if (result->size == 0)
                add_node(result, 1, list2->head->data);
            else
                add_node(result, result->size, list2->head->data);

            del_node(list2, 1);
        }
    }
    clear_linkedlist(list1);
    clear_linkedlist(list2);
    return result;
}


void merge_list_sort_operaations_Welcome(linkedlist *list1, linkedlist *list2, linkedlist *merge_list)
{
    draw_seprator(SEP,40);
    printf("\t Welcome to Merge LinkedList Program \n");
    draw_seprator(SEP,40);

    printf("List 1 : ");
    display_linkedlist(list1);
    printf("\n");

    printf("List 2 : ");
    display_linkedlist(list2);
    printf("\n");

    printf("Merged List : ");
    display_linkedlist(merge_list);
    printf("\n");

    printf("1. Input List1 \n");
    printf("2. Input List2 \n");
    printf("3. Merge Sorted \n");
    printf("4. Exit \n");
}

void input_linkedlist(linkedlist *list)
{
    int n = ask_choice(1, 99999, "Enter total nodes");
    printf("Enter the values seprated by space :");
    for (int i = 1; i <= n; i++)
    {
        int val;
        scanf("%d",&val);
        add_node(list,i,val);
    }
}

void linkedlist_merge_sorted_operations()
{
    linkedlist *list1 = new_linear_list();
    linkedlist *list2 = new_linear_list();
    linkedlist *merge_list = new_linear_list();

    int flag = 0;
    while (flag == 0)
    {
        merge_list_sort_operaations_Welcome(list1, list2, merge_list);
        int ch = ask_choice(1, 6, "Select any option");
        switch (ch)
        {
        case 1:
            input_linkedlist(list1);
            break;

        case 2:
            input_linkedlist(list2);
            break;

        case 3:
            if (list1->head != NULL && list2->head != NULL)
            {
                selection_sort_linkedlist(list1);
                selection_sort_linkedlist(list2);
                merge_list = merge_linkedlist_sorted(list1, list2);
            }
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
    linkedlist_merge_sorted_operations();
}