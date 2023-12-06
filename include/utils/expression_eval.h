#pragma once
#include "../include/parser.h"
#include "../include/memory.h"

int is_node_operator(NodeType type);
int precedence(NodeType type, char *op);
ASTNode *infix_to_postfix(ASTNode **expression, size_t size, ScopeStack *memory);
char *int_to_string(int number);