#include "../include/parser.h"

typedef struct
{
    char *name;
    char *type;
    char *value;
} Variable;

typedef struct
{
    // FIXME: Make it scale automatically
    Variable variables[5000];
    int count;
} SymbolTable;

void init_SymbolTable(SymbolTable *sym_table)
{
    sym_table->count = 0;
}

void addVariable(SymbolTable *table, char *type, char *name, char *value)
{
    // FIXME: Create function to clear the table
    if (table->count < 5000)
    {
        Variable var;
        var.name = strdup(name);
        var.value = strdup(value);
        if (type != NULL)
        {
            var.type = type;
        }
    }
}

ASTNode *evaluate(ASTNode *node)
{
    if (node == NULL)
    {
        return NULL;
    }

    ASTNode *type, *name, *value;
    switch (node->type)
    {
    case NODE_V_DEF:;
        type = evaluate(node->children[0]);
        name = evaluate(node->children[1]);
        value = evaluate(node->children[2]);
        // FIXME: Validate values and create new variable
        printf("%s %s = %s\n", type->value, name->value, value->value);
        break;
    case NODE_ASSIGN:;
        name = evaluate(node->children[0]);
        value = evaluate(node->children[1]);
        // FIXME: Validate values and create new variable
        printf("%s = %s\n", name->value, value->value);
        break;
    case T_VAL:
    case VAL:
    case ID:
    case V_TYPE:
        return node;
    case NODE_EXPRESSION:
        if (node->children_num == 1)
        {
            return node->children[0];
        }
        // FIXME: get expression tree and calculate the value
        return node->children[0];
        break;
    case NODE_LIST_B:
        // FIXME: Get list values
        return node->children[0];
        break;
    default:
        for (size_t i = 0; i < node->children_num; i++)
        {
            evaluate(node->children[i]);
        }
        break;
    }
}