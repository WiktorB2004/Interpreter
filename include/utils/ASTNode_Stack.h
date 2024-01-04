#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../parser.h"

/*!
 * \brief Structure representing a stack of ASTNode pointers.
 *
 * This structure defines a stack data structure specifically designed
 * to hold pointers to ASTNode objects.
 */
typedef struct
{
    ASTNode *data[500]; /**< Array to store ASTNode pointers */
    int top;            /**< Index indicating the top of the stack */
} ASTNodeStack;

/*!
 * \brief Initialization of the stack.
 *
 * Function responsible for the correct initialization of ASTNode Stack.
 */
ASTNodeStack *create_ASTNodeStack();

/*!
 * \brief checking if the stack is empty
 *
 * Function checking if the ASTNode stack is empty.
 * @param stack Pointer to the stack to perform check on
 */
int is_ASTNodeStack_empty(ASTNodeStack *stack);

/*!
 * \brief checking if the stack is full
 *
 * Function checking if the ASTNode stack is full.
 * @param stack Pointer to the stack to perform check on
 */
int is_ASTNodeStack_full(ASTNodeStack *stack);

/*!
 * \brief Pushing node to the top of the stack.
 *
 * Function pushing passed ASTNode to the stack.
 * @param stack Pointer to the stack to which push the item
 * @param value Node to push to the top of the stack
 */
void ASTNodeStack_push(ASTNodeStack *stack, ASTNode *value);

/*!
 * \brief Popping and returning element from the top of the stack.
 *
 * Function popping (removing) one element from the top of the stack.
 * @param stack Pointer to the stack from which to pop the item
 * @return Node from the top
 */
ASTNode *ASTNodeStack_pop(ASTNodeStack *stack);

/*!
 * \brief Returning the top element from the stack.
 *
 * Fuction returning pointer to the top element of the stack.
 * @param stack Pointer to the stack to seek
 * @return The top node from the stack
 */
ASTNode *ASTNodeStack_peek(ASTNodeStack *stack);

/*!
 * \brief Releasing memory allocated by stack.
 *
 * Fuction freeing memory previously allocated by initializing of stack.
 * @param stack Pointer to the stack to free
 */
void free_ASTNodeStack(ASTNodeStack *stack);
