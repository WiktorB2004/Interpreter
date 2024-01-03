#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../parser.h"

typedef struct
{
    ASTNode *data[500];
    int top;
} ASTNodeStack;

/*!
 * Function responsible for the correct initialization of ASTNode Stack
 */
ASTNodeStack *create_ASTNodeStack();

/*!
 * Function checking if the ASTNode stack is empty
 * @param stack Stack to perform check on
 */
int is_ASTNodeStack_empty(ASTNodeStack *stack);

int is_ASTNodeStack_full(ASTNodeStack *stack);
void ASTNodeStack_push(ASTNodeStack *stack, ASTNode *value);
ASTNode *ASTNodeStack_pop(ASTNodeStack *stack);
ASTNode *ASTNodeStack_peek(ASTNodeStack *stack);
void free_ASTNodeStack(ASTNodeStack *stack);
