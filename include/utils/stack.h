#pragma once

typedef struct
{
    int data[500];
    int top;
} Stack;

Stack *create_stack();
int is_empty(Stack *stack);
int is_full(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
int peek(Stack *stack);
void free_stack(Stack *stack);