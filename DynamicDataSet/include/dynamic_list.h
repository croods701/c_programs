#ifndef STDUTIL_H
#define STDUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define Mem_New(type, n) \
    (((size_t)(n) > UINT32_MAX / sizeof(type)) ? NULL : ((type *)malloc((n) * sizeof(type))))

#define New_Int_Object(v, Obj_ptr) \
    Obj_ptr->data = v;             \
    Obj_ptr->byte_size = sizeof(int);

#define New_DataObject(v) _new_dataobj(sizeof(v), &v)

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

DataObj *_new_dataobj(size_t, void *);

int list_resize(ListObj *, size_t);
int list_preallocate_exact(ListObj *, size_t);

ListObj *List_New(size_t);
ListObj *list_new_prealloc(size_t);

inline int valid_index(size_t, size_t);

DataObj *List_GetItem(ListObj *, size_t);
int List_SetItem(ListObj *, size_t, DataObj *);

int ins1(ListObj *, size_t, DataObj *);
int List_Insert(ListObj *, size_t, DataObj *);

int app1(ListObj *, DataObj *);
int List_Append(ListObj *, DataObj *);

DataObj *list_pop_impl(ListObj *, size_t);
DataObj *List_Pop(ListObj *, size_t);

#define Push(list_ptr, data_ptr) List_Append(list_ptr, data_ptr)

#define Pop(list_ptr) list_pop_impl(self, List_Size(self) - 1)

#define Enqueue(list_ptr, data_ptr) List_Append(list_ptr, data_ptr)

#define Dequeue(list_ptr) list_pop_impl(self, 0)

#endif