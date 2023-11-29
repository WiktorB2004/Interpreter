#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../parser.h"

typedef struct
{
    ASTNode *data[500];
    int top;
} ASTNodeStack;

ASTNodeStack *create_ASTNodeStack();
int is_ASTNodeStack_empty(ASTNodeStack *stack);
int is_ASTNodeStack_full(ASTNodeStack *stack);
void ASTNodeStack_push(ASTNodeStack *stack, ASTNode *value);
ASTNode *ASTNodeStack_pop(ASTNodeStack *stack);
ASTNode *ASTNodeStack_peek(ASTNodeStack *stack);
void free_ASTNodeStack(ASTNodeStack *stack);
