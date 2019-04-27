#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

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

//=======================================================================================================================
#define Mem_New(type, n) \
    (((size_t)(n) > UINT32_MAX / sizeof(type)) ? NULL : ((type *)malloc((n) * sizeof(type))))
#define MemVar_New(type) Mem_New(type, 1)

#define New_DataObject(v) _new_dataobj(sizeof(v), &v)

#define Push(list_ptr, data_ptr) List_Append(list_ptr, data_ptr)

#define Pop(list_ptr) list_pop_impl(list_ptr, List_Size(list_ptr) - 1)

#define Enqueue(list_ptr, data_ptr) List_Append(list_ptr, data_ptr)

#define Dequeue(list_ptr) list_pop_impl(list_ptr, 0)

//=======================================================================================================================

//=======================================================================================================================
typedef struct DataObj;
typedef struct DataObj
{
    size_t byte_size;
    void *data;
} DataObj;

typedef struct ListObj
{
    DataObj **ob_item;
    size_t allocated;
    size_t size;
} ListObj;

DataObj *_new_dataobj(size_t byte_size, void *data)
{
    DataObj *new_dataobj = MemVar_New(DataObj);
    new_dataobj->byte_size = byte_size;
    new_dataobj->data = malloc(sizeof(byte_size));
    memcpy(new_dataobj->data, data, byte_size);
    return new_dataobj;
}

int list_resize(ListObj *self, size_t newsize)
{
    DataObj **items;
    size_t new_allocated, num_allocated_bytes;
    size_t allocated = self->allocated;

    /* Bypass realloc() when a previous overallocation is large enough
       to accommodate the newsize.  If the newsize falls lower than half
       the allocated size, then proceed with the realloc() to shrink the list.
    */
    if (allocated >= newsize && newsize >= (allocated >> 1))
    {
        assert(self->ob_item != NULL || newsize == 0);
        self->size = newsize;
        return 0;
    }

    /* This over-allocates proportional to the list size, making room
     * for additional growth.  The over-allocation is mild, but is
     * enough to give linear-time amortized behavior over a long
     * sequence of appends() in the presence of a poorly-performing
     * system realloc().
     * The growth pattern is:  0, 4, 8, 16, 25, 35, 46, 58, 72, 88, ...
     * Note: new_allocated won't overflow because the largest possible value
     *       is PY_SSIZE_T_MAX * (9 / 8) + 6 which always fits in a size_t.
     */
    new_allocated = newsize + (newsize >> 3) + (newsize < 9 ? 3 : 6);
    if (new_allocated > UINT32_MAX / sizeof(DataObj *))
    {
        fprintf(stderr, "No Memory \n.");
        return -1;
    }

    if (newsize == 0)
    {
        self->size = newsize;
        self->allocated = 0;
        return 0;
    }

    num_allocated_bytes = new_allocated * sizeof(DataObj *);
    items = (DataObj **)realloc(self->ob_item, num_allocated_bytes);
    if (items == NULL)
    {
        fprintf(stderr, "No Memory \n.");
        return -1;
    }
    self->ob_item = items;
    self->size = newsize;
    self->allocated = new_allocated;
    return 0;
}

int list_preallocate_exact(ListObj *self, size_t size)
{
    assert(self->ob_item == NULL);
    assert(size > 0);

    DataObj **items = (DataObj **)malloc(sizeof(ListObj) * size);
    if (items == NULL)
    {
        fprintf(stderr, "No Memory \n.");
        return -1;
    }
    self->ob_item = items;
    self->allocated = size;
    return 0;
}

ListObj *List_New(size_t size)
{
    ListObj *op;

    if (size < 0)
    {
        fprintf(stderr, "Bad Internal Call. \n");
        return NULL;
    }

    op = (ListObj *)malloc(sizeof(ListObj));
    if (op == NULL)
        return NULL;

    if (size <= 0)
        op->ob_item = NULL;
    else
    {
        op->ob_item = (DataObj **)malloc(size * sizeof(DataObj *));
        if (op->ob_item == NULL)
        {
            fprintf(stderr, "No Memory");
            return NULL;
        }
    }
    op->size = size;
    op->allocated = size;
    return op;
}

ListObj *list_new_prealloc(size_t size)
{
    ListObj *op = (ListObj *)List_New(0);
    if (size == 0 || op == NULL)
    {
        return (ListObj *)op;
    }
    assert(op->ob_item == NULL);
    op->ob_item = (DataObj **)malloc(size * sizeof(DataObj *));
    if (op->ob_item == NULL)
    {
        fprintf(stderr, "No Memory");
        return NULL;
    }
    op->allocated = size;
    return (ListObj *)op;
}

size_t List_Size(ListObj *op)
{
    return op->size;
}

static inline int valid_index(size_t i, size_t limit)
{
    /* The cast to size_t lets us use just a single comparison
       to check whether i is in the range: 0 <= i < limit.

       See:  Section 14.2 "Bounds Checking" in the Agner Fog
       optimization manual found at:
       https://www.agner.org/optimize/optimizing_cpp.pdf
    */
    return i < limit;
}

DataObj *List_GetItem(ListObj *op, size_t i)
{

    if (!valid_index(i, List_Size(op)))
    {
        fprintf(stderr, "Index out of range. \n");
        return NULL;
    }
    return op->ob_item[i];
}

int List_SetItem(ListObj *op, size_t i, DataObj *newitem)
{
    DataObj **p;

    if (!valid_index(i, List_Size(op)))
    {

        fprintf(stderr, "list assignment index out of range");
        return -1;
    }
    p = op->ob_item + i;
    *p = newitem;
    return 0;
}

int ins1(ListObj *self, size_t where, DataObj *v)
{
    size_t i, n = List_Size(self);
    DataObj **items;

    if (n == UINT32_MAX)
    {
        fprintf(stderr, "Cannot add more items");
        return -1;
    }

    if (list_resize(self, n + 1) < 0)
        return -1;

    if (where < 0)
    {
        where += n;
        if (where < 0)
            where = 0;
    }
    if (where > n)
        where = n;
    items = self->ob_item;
    for (i = n; --i >= where;)
        items[i + 1] = items[i];
    items[where] = v;
    return 0;
}

int List_Insert(ListObj *op, size_t where, DataObj *newitem)
{

    return ins1(op, where, newitem);
}

int app1(ListObj *self, DataObj *v)
{
    size_t n = List_Size(self);

    assert(v != NULL);
    if (n == UINT32_MAX)
    {
        fprintf(stderr, "Cannot add more items");
        return -1;
    }

    if (list_resize(self, n + 1) < 0)
        return -1;

    self->ob_item[n] = v;
    return 0;
}

int List_Append(ListObj *op, DataObj *newitem)
{
    if (newitem != NULL)
        return app1(op, newitem);

    return -1;
}

DataObj *list_pop_impl(ListObj *self, size_t index)
{
    DataObj **items;
    DataObj *v;
    int status;
    size_t n = List_Size(self);

    if (n == 0)
    {
        /* Special-case most common failure cause */
        fprintf(stderr, "pop from empty list");
        return NULL;
    }
    if (index < 0)
        index += n;
    if (!valid_index(index, n))
    {
        fprintf(stderr, "pop index out of range");
        return NULL;
    }
    v = self->ob_item[index];
    if (index == n - 1)
    {
        status = list_resize(self, n - 1);
        if (status >= 0)
            return v; /* and v now owns the reference the list had */
        else
            return NULL;
    }

    items = self->ob_item;
    for (size_t i = index-1; ++i < n - 1;)
        items[i] = items[i + 1];
    list_resize(self, n - 1);

    return v;
}

DataObj *List_Pop(ListObj *self, size_t index)
{
    return list_pop_impl(self, index);
}

//==========================================================================================================================

void print_int_list(ListObj *list)
{
    if (List_Size(list) > 0)
    {
        for (size_t i = 0; i < List_Size(list) - 1; i++)
            printf("%d ", *(int *)List_GetItem(list, i)->data);
        printf("%d \n", *(int *)List_GetItem(list, List_Size(list) - 1)->data);
    }else{
        printf("List EMPTY \n");
    }
}

void print_menu(ListObj *current_list)
{
    printf("\t Welcome to Queue & Stacks \n");

    printf("Current List : ");
    print_int_list(current_list);

    printf("\t 1. Push OR Enqueue. \n");
    printf("\t 2. Pop \n");
    printf("\t 3. Dequeue \n");
    printf("\t 4. Exit \n");
}

int main()
{
    int flag = 0;
    ListObj *list = List_New(0);

    while (flag == 0)
    {
        clear();
        print_menu(list);
        printf("Select any option: ");
        int ch;
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\n Enter the value you wish to add in list : ");
            int val;
            scanf("%d", &val);
            Push(list, New_DataObject(val));
            break;
        case 2:
            if (List_Size(list) <= 0)
            {
                printf(" \n UNDERFLOW \n");
            }
            else
            {
                printf("%d has been poped out. \n", *(int *)Pop(list)->data);
            }
            break;
        case 3:
            if (List_Size(list) <= 0)
            {
                printf(" \n UNDERFLOW \n");
            }
            else
            {
                printf("%d has been dequeued. \n", *(int *)Dequeue(list)->data);
            }
            break;
        case 4:
            flag = 1;
            break;

        default:
            printf("\n Please enter appropriate option. \n");
            break;
        }
        pause();
    }

    return 0;
}