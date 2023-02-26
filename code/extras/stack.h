#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stddef.h>
#define STACK_SIZE 256

typedef struct stack
{
    int64_t *data;
    size_t p;
} stack_t;

stack_t *stack_init();
void stack_free(stack_t *stack);
void stack_push(stack_t *stack, int64_t n);
//int64_t *stack_pop(stack_t *stack);
int64_t stack_pop(stack_t *stack);

#endif