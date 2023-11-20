#include <stdio.h>
#include <stdlib.h>
#include "../include/utils/stack.h"

Stack *create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack != NULL)
    {
        stack->top = -1; // Empty stack
    }
    return stack;
}

int is_empty(Stack *stack)
{
    return stack->top == -1;
}

int is_full(Stack *stack)
{
    return stack->top == 500 - 1;
}

void push(Stack *stack, int value)
{
    if (is_full(stack))
    {
        printf("Stack overflow!\n");
        return;
    }
    stack->data[++stack->top] = value;
}

int pop(Stack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack underflow!\n");
        return -1; // Return some error value
    }
    return stack->data[stack->top--];
}

int peek(Stack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack is empty!\n");
        return -1; // Return some error value
    }
    return stack->data[stack->top];
}

void free_stack(Stack *stack)
{
    free(stack);
}
