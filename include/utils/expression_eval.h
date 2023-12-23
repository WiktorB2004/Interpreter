#pragma once
#include "../parser.h"
#include "../memory.h"

int is_node_operator(NodeType type);
int precedence(NodeType type, char *op);
ASTNode *infix_to_postfix(ASTNode **expression, size_t size, ScopeStack *memory);
char *num_to_string(double number);
ASTNode *evaluate_expression(ASTNode *expression);