#include <stddef.h>

#define ssize_t size_t

#define object_VAR_HEAD


typedef struct _object {
    ssize_t ob_refcnt;
    struct _typeobject *ob_type;
} Object;

/* Cast argument to Object* type. */
#define Object_CAST(op) ((Object*)(op))

#define Obj_REFCNT(ob)           (Object_CAST(ob)->ob_refcnt)
#define Obj_TYPE(ob)             (Object_CAST(ob)->ob_type)


typedef void (*destructor)(Object *);
