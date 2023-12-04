#pragma once
#include "../include/interpreter.h"
#include "../include/parser.h"

// FIXME: Move structs into separate file
typedef struct
{
    char *name;
    char *type;
    ASTNode *params;
    ASTNode *value;
} Variable;

typedef struct
{
    // FIXME: Make it scale automatically
    Variable variables[5000];
    int count;
} SymbolTable;

ASTNode *evaluate(ASTNode *node, SymbolTable *memory);
void init_SymbolTable(SymbolTable *sym_table);
void print_SymbolTable(SymbolTable *table);