#pragma once
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/memory.h"

/*!
 * \brief AST evaluation.
 *
 * The function recursively evaluates AST (Abstract Syntax Tree).
 *
 * @param node pointer to the root node of the AST
 * @param memory pointer to ScopeStack which handles user program memory manipulation and scoping
 */
ASTNode *evaluate(ASTNode *node, ScopeStack *memory);