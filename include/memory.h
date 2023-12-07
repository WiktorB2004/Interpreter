#pragma once
#include "parser.h"

typedef struct
{
    char *name;
    char *type;
    ASTNode *params;
    ASTNode *value;
    ASTNode *return_value;
} Variable;

typedef struct
{
    Variable *entries;
    size_t capacity;
    size_t size;
} SymbolTable;

typedef struct
{
    SymbolTable *items;
    int top;
    int max_size;
} ScopeStack;

void init_SymbolTable(SymbolTable *table, size_t capacity);
void init_ScopeStack(ScopeStack *stack, int max_size);
void push_scope(ScopeStack *stack, size_t table_capacity);
void pop_scope(ScopeStack *stack);
void add_variable(ScopeStack *stack, char *type, char *name, ASTNode *value, ASTNode *params);
Variable *find_variable(ScopeStack *stack, const char *name);
void modify_variable_value(ScopeStack *memory, char *name, ASTNode *value_node);