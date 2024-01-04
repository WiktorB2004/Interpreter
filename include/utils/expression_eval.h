#pragma once
#include "../parser.h"
#include "../memory.h"

/*!
 * \brief Checks if the node type is operator.
 *
 * Function checking if type is any of the operators (Logic/Arithmetic/Relational).
 * @param type Any type of the node to check
 * @return returning 1/0 as true/false
 */
int is_node_operator(NodeType type);

/*!
 * \brief Returning operator precendence.
 *
 * Fuction determining operator precendence
 * @param type Type of the Node - operator type
 * @param op value of the node - operator value
 * @return integer correspondning to the precendence of the operator
 */
int precedence(NodeType type, char *op);

/*!
 * \brief Converting expression from infix to postfix notation.
 *
 * Fuction converting order of the expression node childreen from infix to postfix notation
 * and inserting values of the variables from the program memory
 * @param expression Pointer to the ASTNode pointer containing elements of the expression
 * @param size Size of the expression - number of the expression root node children
 * @param memory Pointer to the memory stack of the user program
 * @return ASTNode containing expression in postfix notation
 */
ASTNode *infix_to_postfix(ASTNode **expression, size_t size, ScopeStack *memory);

/*!
 * \brief Converting num to string.
 *
 * Function converting double to string (char *)
 * @param number number to convert
 * @return string (char*) containing the provided number
 */
char *num_to_string(double number);

/*!
 * \brief Evaluating expression and returning value node.
 *
 * Function evaluating the expression in postfix notation
 * @param expression Pointer to ASTNode with
 * the type of NODE_EXPRESSION and having its elements ordered in posfix notation stored as its
 * childreen
 * @return ASTNode containing the result of evaluated expression
 */
ASTNode *evaluate_expression(ASTNode *expression);