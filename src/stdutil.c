#include <stdutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Note:-
    Very Bad implementation for the sake of prortablity and laziness.
    Should be using ANSI codes in POSIX and windows.h in WIN */
void clear()
{
    system("cls||clear");
}

/*Note:-
    Very Bad implementation
    Should not be using fflush() - http://www.gidnetwork.com/b-57.html
*/
void pause()
{
    fflush(stdin); //to clear buffer
    getchar();
}

//STACK-----------------------------------------------------------------

stack_t get_stack(int block_size, int size)
{
    stack_t new_stack;
    new_stack.block_size = block_size;
    new_stack.size = size - 1;
    new_stack.top = -1;
    new_stack.data = malloc(size * new_stack.block_size);

    return new_stack;
}

int push(stack_t *stack, void *value)
{

    if (stack->data == NULL)
        return MEMORY_ERROR;
    if (stack->top >= stack->size)
        return OVERFLOW;

    int index = ((++(stack->top)) * stack->block_size);

    memcpy(&(stack->data[index]), value, stack->block_size);
    return 0;
}

int pop(stack_t *stack, void *value)
{
    if (stack->data == NULL)
        return MEMORY_ERROR;
    if (stack->top < 0)
        return UNDERFLOW;

    int index = (stack->top-- * stack->block_size);
    memcpy(value, &(stack->data[index]), stack->block_size);

    return 0;
}

void free_stack(stack_t *data_t)
{
    free(data_t->data);
}