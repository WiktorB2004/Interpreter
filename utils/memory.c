#include "../include/memory.h"
#include "../include/parser.h"

// Initialize a symbol table
void init_SymbolTable(SymbolTable *table, size_t capacity)
{
    table->entries = (Variable *)malloc(capacity * sizeof(Variable));
    table->capacity = capacity;
    table->size = 0;
}

// Initialize a scope stack
void init_ScopeStack(ScopeStack *stack, int max_size)
{
    stack->items = (SymbolTable *)malloc(max_size * sizeof(SymbolTable));
    stack->top = -1;
    stack->max_size = max_size;
}

// Push a new scope onto the scope stack
void push_scope(ScopeStack *stack, size_t table_capacity)
{
    if (stack->top >= stack->max_size - 1)
    {
        printf("Scope stack overflow\n");
        exit(EXIT_FAILURE);
    }
    init_SymbolTable(&(stack->items[++stack->top]), table_capacity);
}

// Pop the top scope from the scope stack
void pop_scope(ScopeStack *stack)
{
    if (stack->top < 0)
    {
        printf("Scope stack underflow\n");
        exit(EXIT_FAILURE);
    }
    free(stack->items[stack->top--].entries);
}

// Add a variable to the current scope's symbol table
void add_variable(ScopeStack *stack, char *type, char *name, ASTNode *value, ASTNode *params)
{
    if (stack->top < 0)
    {
        printf("No active scope\n");
        return;
    }
    SymbolTable *current_scope = &(stack->items[stack->top]);
    if (current_scope->size >= current_scope->capacity)
    {
        printf("Symbol table overflow\n");
        exit(EXIT_FAILURE);
    }
    Variable *entry = &(current_scope->entries[current_scope->size++]);
    if (value != NULL && type != NULL && name != NULL)
    {
        entry->type = strdup(type);
        entry->name = strdup(name);
        entry->value = value;
        entry->params = params;
    }
}

// Search for a variable in the current scope and its outer scopes
Variable *find_variable(ScopeStack *stack, const char *name)
{
    for (int i = stack->top; i >= 0; --i)
    {
        SymbolTable *current_scope = &(stack->items[i]);
        for (size_t j = 0; j < current_scope->size; ++j)
        {
            if (strcmp(current_scope->entries[j].name, name) == 0)
            {
                return &current_scope->entries[j];
            }
        }
    }
    printf("Variable '%s' not found\n", name);
    exit(EXIT_FAILURE);
}

void modify_variable_value(ScopeStack *memory, char *name, ASTNode *value_node)
{
    Variable *target = find_variable(memory, name);
    target->value = value_node;
}