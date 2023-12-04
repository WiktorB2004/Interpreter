#include <string.h>
#include "../include/interpreter.h"
#include "../include/parser.h"

void init_SymbolTable(SymbolTable *sym_table)
{
    sym_table->count = 0;
}

void print_SymbolTable(SymbolTable *table)
{
    printf("========== Symbol Table ==========\n");
    for (int i = 0; i < table->count; i++)
    {
        printf("%s %s\n", table->variables[i].name, table->variables[i].type);
        print_ASTree(table->variables[i].params, 0);
        print_ASTree(table->variables[i].value, 0);
    }
    printf("=================================\n");
}

void enter_scope(SymbolTable **memory_stack, int current_scope)
{
    if (current_scope < 499)
    {
        memory_stack[++current_scope] = (SymbolTable *)malloc(sizeof(SymbolTable));
        memory_stack[current_scope]->count = 0;
    }
    else
    {
        printf("Maximum scope depth reached!\n");
    }
}

Variable *create_variable(char *type, char *name, ASTNode *value, ASTNode *params)
{
    Variable *new_variable = (Variable *)malloc(sizeof(Variable));
    if (new_variable == NULL)
    {
        fprintf(stderr, "Memory allocation failed for creating ASTNode.\n");
        exit(EXIT_FAILURE);
    }
    if (value != NULL && type != NULL && name != NULL)
    {
        new_variable->type = strdup(type);
        new_variable->name = strdup(name);
        new_variable->value = value;
        new_variable->params = params;
    }
    return new_variable;
}

void insert_variable(SymbolTable *table, Variable *var)
{
    if (table->count < 5000)
    {
        table->variables[table->count++] = *var;
    }
    else
    {
        printf("Variable table is full!\n");
    }
}

void modify_variable_value(SymbolTable *table, char *name, ASTNode *value_node)
{
    for (int i = 0; i < table->count; i++)
    {
        if (strcmp(table->variables[i].name, name) == 0)
        {
            table->variables[i].value = value_node;
            return;
        }
    }
    fprintf(stderr, "Changing value of nonexistent variable.\n");
    exit(EXIT_FAILURE);
}

Variable *find_variable(SymbolTable *table, char *name)
{
    for (int i = 0; i < table->count; i++)
    {
        if (strcmp(table->variables[i].name, name) == 0)
        {
            return &table->variables[i];
        }
    }
    fprintf(stderr, "Value is not in memory.\n");
    exit(EXIT_FAILURE);
}

void exit_scope(SymbolTable **memory_stack, int current_scope)
{
    if (current_scope >= 0)
    {
        free(memory_stack[current_scope]);
        current_scope--;
    }
}

ASTNode *evaluate(ASTNode *node, SymbolTable *memory)
{
    if (node == NULL)
    {
        return NULL;
    }

    ASTNode *type, *name, *value, *params;
    switch (node->type)
    {
    // SECTION: Variables
    case NODE_V_DEF:;
        type = evaluate(node->children[0], memory);
        name = evaluate(node->children[1], memory);
        value = evaluate(node->children[2], memory);
        // FIXME: Validate values and create new variable
        insert_variable(memory, create_variable(type->value, name->value, value, NULL));
        break;
    case NODE_ASSIGN:;
        name = evaluate(node->children[0], memory);
        value = evaluate(node->children[1], memory);
        // FIXME: Validate values and create new variable
        modify_variable_value(memory, name->value, value);
        break;
    // SECTION: Expressions and values
    case NODE_T_VAL:
    case NODE_VAL:
    case NODE_ID:
    case NODE_V_TYPE:
        return node;
    case NODE_EXPRESSION:
        if (node->children_num == 1)
        {
            return node->children[0];
        }
        return create_ASTNode(NODE_VAL, "Expression_Dummy");
        break;
    case NODE_LIST_B:
        // FIXME: Get list values
        return evaluate(node->children[0], memory);
        break;
    // SECTION: Functions
    case NODE_SCOPE:
        if (strcmp(node->value, "Function_Scope") == 0)
        {
            name = evaluate(node->children[0], memory);
            type = node->children[1];
            params = node->children[2];
            value = node->children[3];
            // FIXME: Save function as ASTNode so when called it will pass the f_body and params
            insert_variable(memory, create_variable(type->value, name->value, value, params));
        }
        else if (strcmp(node->value, "While_Loop") == 0)
        {
            params = node->children[0];
            value = node->children[1];
            // FIXME: Interpret while loop by evaluating "value" (body) while the condition is true
            printf("While loop:\n");
            printf("Loop condition:");
            print_ASTree(params, 0);
            printf("Loop body:");
            print_ASTree(value, 0);
            printf("\n");
        }
        else if (strcmp(node->value, "Conditional_Scope") == 0)
        {
            params = node->children[0];
            value = node->children[1];
            if (node->children[2] != NULL)
            {
                name = node->children[2];
            }
            // FIXME: Interpret if by checking condition and passing correct node to evaluate
            printf("IF / ELSE:\n");
            printf("Condition:\n");
            print_ASTree(params, 0);
            printf("If:\n");
            print_ASTree(value, 0);
            printf("Else:\n");
            print_ASTree(name, 0);
            printf("\n");
        }
        else if (strcmp(node->value, "Function_Body") == 0)
        {
            for (size_t i = 0; i < node->children_num; i++)
            {
                evaluate(node->children[i], memory);
            }
        }
        break;
    // SECTION: Keywords
    case NODE_KEYWORD:
        if (strcmp(node->value, "Print") == 0)
        {
            // FIXME: Correctly print expiressions etc.
            // FIXME: Correctly insert newlines etc.
            value = node->children[0];
            switch (value->type)
            {
            case NODE_ID:;
                Variable *var = find_variable(memory, value->value);
                printf("%s\n", var->value->value);
                break;
            case NODE_VAL:
            case NODE_T_VAL:
                printf("%s\n", value->value);
                break;
            case NODE_EXPRESSION:
                break;
            default:
                break;
            }
        }
        break;
    // SECTION: Function call
    case NODE_FUNC_CALL:
        name = evaluate(node->children[0], memory);
        params = node->children[1];
        Variable *function = find_variable(memory, name->value);
        evaluate(function->value, memory);
        break;
    default:
        for (size_t i = 0; i < node->children_num; i++)
        {
            evaluate(node->children[i], memory);
        }
        break;
    }
}