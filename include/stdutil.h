#ifndef STDUTIL_H
#define STDUTIL_H
//--------------------------------------------------------------------------------------------

#include <stdint.h>
#include <stddef.h>

typedef struct stack_t
{
    int block_size;
    int size;
    int top;
    uint8_t *data;
} stack_t;

typedef enum
{
    SUCESS,
    OVERFLOW,
    UNDERFLOW,
    MEMORY_ERROR
} my_error;

//--------------------------------------------------------------------------------------------

void pause();

void clear();

//--------------------------------------------------------------------------------------------

/*
Create a new stack object
Args:
    int block_size: Specifies the byte width of each element in stack.
                    Example:- if stack is to store 'int', then sizeof(int)
                    should be pass.
    int size: Specifies the MAX size of stack.
Return:
    New stack object
*/
stack_t get_stack(int, int);

/*
Push element in stack
Args:
    stack_t* : Pointer to the stack object.
    void* : Pointer of the variable to push.
Return:
    From enum my_errors:
    [0]SUCESS, [1]OVERFLOW [3]MEMORRY_ERROR
*/
int push(stack_t *, void *);

/*
Pop element from stack
Args:
    stack_t* : Pointer to the stack object.
    void* : Pointer of the variable to store poped value.
Return:
    From enum my_errors:
    [0]SUCESS, [2]UNDERFLOW [3]MEMORRY_ERROR
*/
int pop(stack_t *, void *);

/*Free the memory allocated to stack*/
void free_stack(stack_t *);

//--------------------------------------------------------------------------------------------
#endif