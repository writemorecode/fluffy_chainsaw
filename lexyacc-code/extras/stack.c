#include <stdlib.h>

#include "stack.h"

stack_t *stack_init()
{
    stack_t *stack = calloc(1, sizeof(stack_t));
    if (stack == NULL)
    {
        return NULL;
    }
    stack->data = calloc(STACK_SIZE, sizeof(int64_t));
    if (stack->data == NULL)
    {
        free(stack);
        return NULL;
    }
    stack->p = 0;
    return stack;
}

void stack_free(stack_t *stack)
{
    if (stack == NULL)
    {
        return;
    }
    free(stack->data);
    free(stack);
}

void stack_push(stack_t *stack, int64_t n)
{
    if (stack == NULL)
    {
        return;
    }
    stack->p++;
    if (stack->p == STACK_SIZE)
    {
        return;
    }
    stack->data[stack->p] = n;
}

//int64_t *stack_pop(stack_t *stack)
int64_t stack_pop(stack_t *stack)
{
    int64_t n = stack->data[stack->p];
    stack->p--;
    return n;
    // if (stack == NULL)
    // {
    //     return NULL;
    // }
    // // Every pop must be preceded by a push
    // if (stack->p == 0)
    // {
    //     // Stack empty
    //     return NULL;
    // }
    // int64_t *p = &(stack->data[stack->p]);
    // stack->p--;
    // return p;
}
