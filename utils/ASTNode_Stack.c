#include <stdio.h>
#include <stdlib.h>
#include "../include/utils/ASTNode_Stack.h"
#include "../include/parser.h"

ASTNodeStack *create_ASTNodeStack()
{
    ASTNodeStack *stack = (ASTNodeStack *)malloc(sizeof(ASTNodeStack));
    if (stack != NULL)
    {
        stack->top = -1; // Empty stack
    }
    return stack;
}

int is_ASTNodeStack_empty(ASTNodeStack *stack)
{
    return stack->top == -1;
}

int is_ASTNodeStack_full(ASTNodeStack *stack)
{
    return stack->top == 500 - 1;
}

void ASTNodeStack_push(ASTNodeStack *stack, ASTNode *value)
{
    if (is_ASTNodeStack_full(stack))
    {
        printf("Stack overflow!\n");
        return;
    }
    stack->data[++stack->top] = value;
}

ASTNode *ASTNodeStack_pop(ASTNodeStack *stack)
{
    if (is_ASTNodeStack_empty(stack))
    {
        printf("Stack underflow!\n");
        return NULL; // Return some error value or handle it accordingly
    }
    return stack->data[stack->top--];
}

ASTNode *ASTNodeStack_peek(ASTNodeStack *stack)
{
    if (is_ASTNodeStack_empty(stack))
    {
        printf("Stack is empty!\n");
        return NULL; // Return some error value or handle it accordingly
    }
    return stack->data[stack->top];
}

void free_ASTNodeStack(ASTNodeStack *stack)
{
    free(stack);
}