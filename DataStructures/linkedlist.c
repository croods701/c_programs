#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

void clear()
{
    system("cls||clear");
}
void pause()
{
    fflush(stdin);
    fflush(stdin);
    getchar();
}

#define New_Mem(type) ((type *)malloc(sizeof(type)))

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = *x;
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
    while (temp != NULL)
    {
        printf("|%d|%p|    ", temp->data,temp);
        temp = temp->next;
    }
}

linkedlist *merge_linkedlists(linkedlist *list1, linkedlist *list2)
{
    linkedlist *big_list = new_linear_list();
    big_list->head = list1->head;
    big_list->size = list1->size + list2->size;

    get_node_by_pos(list1, list1->size)->next = get_node_by_pos(list2, 1);
    free(list1);
    free(list2);

    return big_list;
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
                // swap(&(i->data), &(j->data));
            }
        }
    }
    return list;
}

linkedlist *reverse_linkedlist(linkedlist *list)
{
    int temp;
    for (int i = 1; i <= list->size / 2; i++)
    {
        int rev_pos = (list->size) - i + 1;
        node *x = get_node_by_pos(list, rev_pos);
        node *y = get_node_by_pos(list, i);

        temp = x->data;
        x->data = y->data;
        y->data = temp;
    }
    return list;
}

linkedlist *merge_linkedlist_sorted(linkedlist *list1, linkedlist *list2)
{
    assert(list1->head != NULL || list2->head != NULL);
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

int test()
{
    linkedlist *mylist1 = new_linear_list();
    linkedlist *mylist2 = new_linear_list();
    linkedlist *mylist_merged = new_linear_list();
    for (int i = 1; i < 6; i++)
    {
        add_node(mylist1, i, i);
    }
    for (int j = 3; j < 10; j++)
    {
        add_node(mylist2, j - 6, j);
    }

    for (int i = 1; i <= mylist1->size; i++)
    {
        printf("%d \n", get_node_by_pos(mylist1, i)->data);
    }

    printf("\n");

    for (int i = 1; i <= mylist2->size; i++)
    {
        printf("%d \n", get_node_by_pos(mylist2, i)->data);
    }

    // node *find_node = get_node_by_val(mylist, 5);
    // if (find_node != NULL)
    //     printf("\n%d \n\n", find_node->data);
    int status = add_node(mylist1, 2, 0);
    status = add_node(mylist2, 1, -5);
    selection_sort_linkedlist(mylist1);
    selection_sort_linkedlist(mylist2);
    // reverse_linkedlist(mylist);
    mylist_merged = merge_linkedlist_sorted(mylist1, mylist2);

    printf("\n");

    for (int i = 1; i <= mylist_merged->size; i++)
    {
        printf("%d \n", get_node_by_pos(mylist_merged, i)->data);
    }
}

void welcome()
{
    printf("Welcome to LinkedList Program");
}

void linkedlist_operations_welcome(linkedlist *list)
{
    printf("\t Welcome to LinkedList Program \n");

    printf("Current List : ");
    display_linkedlist(list);
    printf("\n");

    printf("1. Add Node \n");
    printf("2. Del Node \n");
    printf("3. Show No.of Node \n");
    printf("4. Search (Linear) \n");
    printf("5. Sort (Selection) \n");
    printf("6. Reverse \n");
    printf("7. Exit \n");
}

void merge_list_sort_operaations_Welcome(linkedlist *list1, linkedlist *list2, linkedlist *merge_list)
{
    printf("\t Welcome to Merge LinkedList Program \n");

    printf("List 1 : ");
    display_linkedlist(list1);
    printf("\n");

    printf("List 2 : ");
    display_linkedlist(list2);
    printf("\n");

    printf("Merged List : ");
    display_linkedlist(merge_list);
    printf("\n");

    printf("1. Operate List 1 \n");
    printf("2. Operate List 2 \n");
    printf("3. Merge Sorted \n");
    printf("4. Exit \n");
}

void linkedlist_operations(linkedlist *list)
{
    int flag = 0;

    while (flag == 0)
    {
        clear();
        linkedlist_operations_welcome(list);
        // printf("Select any option: ");
        // int ch;
        // scanf("%d", &ch);
        int ch = ask_choice(1, 7, "Select any option");

        switch (ch)
        {
        case 1:
            printf("\nEnter the index : ");
            int index, val;
            scanf("%d", &index);

            printf("Enter the value you wish to add in list : ");
            scanf("%d", &val);

            int status = add_node(list, index, val);
            if (status == -1)
            {
                printf("[ERROR] OverFlow. \n");
            }
            else if (status == -2)
            {
                printf("[ERROR] UnderFlow. \n");
            }

            break;

        case 2:
            printf("\nEnter the index : ");
            int i;
            scanf("%d", &i);

            int res = del_node(list, i);
            if (res == -1)
            {
                printf("[ERROR] OverFlow. \n");
            }
            else if (res == -2)
            {
                printf("[ERROR] UnderFlow. \n");
            }

            break;

        case 3:
            printf("\nSize of List is : %d", list->size);
            break;

        case 4:
            printf("\nEnter the value you want to search : ");
            int v;
            scanf("%d", &v);

            node *find = get_node_by_val(list, v);
            if (find == NULL)
            {
                printf("%d is not present in list. \n", v);
            }
            else
            {
                printf("%d is present at node located at %p. \n", v, find);
            }
            break;

        case 5:
            if (list->head != NULL)
                selection_sort_linkedlist(list);
            break;
        case 6:
            reverse_linkedlist(list);
            break;

        case 7:
            flag = 1;
            break;

        default:
            break;
        }
        pause();
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
        clear();
        merge_list_sort_operaations_Welcome(list1, list2, merge_list);

        int ch = ask_choice(1, 6, "Select any option");

        switch (ch)
        {
        case 1:
            linkedlist_operations(list1);
            break;

        case 2:
            linkedlist_operations(list2);
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
    // test();
}