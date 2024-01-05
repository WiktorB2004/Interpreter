#pragma once
#include "parser.h"

/*!
 * \brief Represents a variable in the memory scope.
 *
 * This structure defines a variable with a name, type, parameters, value, and return value.
 */
typedef struct
{
    char *name;            /**< Name of the variable */
    char *type;            /**< Type of the variable */
    ASTNode *params;       /**< Parameters associated with the variable */
    ASTNode *value;        /**< Value associated with the variable */
    ASTNode *return_value; /**< Return value associated with the variable */
} Variable;

/*!
 * \brief Represents a symbol table data structure.
 *
 * This structure defines a symbol table containing entries - variables, capacity, and size information.
 * It makes possible to store variables as key-value pairs inside the memory.
 */
typedef struct
{
    Variable *entries; /**< Array of Variable entries */
    size_t capacity;   /**< Maximum capacity of the symbol table - variable storage capacity */
    size_t size;       /**< Current size of the symbol table */
} SymbolTable;

/*!
 * \brief Represents a stack of memory scopes.
 *
 * This structure defines a stack of SymbolTables to manage memory scopes.
 */
typedef struct
{
    SymbolTable *items; /**< Array of SymbolTables */
    int top;            /**< Index indicating the top of the stack */
    int max_size;       /**< Maximum size of the stack - scopes capacity */
} ScopeStack;

/*!
 * \brief Initializes a SymbolTable with a specified capacity.
 *
 * @param table Pointer to the SymbolTable to be initialized.
 * @param capacity Initial capacity of the SymbolTable.
 */
void init_SymbolTable(SymbolTable *table, size_t capacity);

/*!
 * \brief Initializes a ScopeStack with a specified maximum size.
 *
 * @param stack Pointer to the ScopeStack to be initialized.
 * @param max_size Maximum size of the ScopeStack.
 */
void init_ScopeStack(ScopeStack *stack, int max_size);

/*!
 * \brief Pushes a new scope into the ScopeStack.
 *
 * @param stack Pointer to the ScopeStack.
 * @param table_capacity Initial capacity of the new SymbolTable to be pushed.
 */
void push_scope(ScopeStack *stack, size_t table_capacity);

/*!
 * \brief Pops the top scope from the ScopeStack.
 *
 * @param stack Pointer to the ScopeStack.
 */
void pop_scope(ScopeStack *stack);

/*!
 * \brief Adds a new variable to the current (top) scope in the ScopeStack.
 *
 * @param stack Pointer to the ScopeStack.
 * @param type Type of the variable.
 * @param name Name of the variable.
 * @param value Value associated with the variable.
 * @param params Parameters associated with the variable.
 */
ASTNode *add_variable(ScopeStack *stack, char *type, char *name, ASTNode *value, ASTNode *params);

/*!
 * \brief Finds a variable by name within the ScopeStack.
 *
 * @param stack Pointer to the ScopeStack.
 * @param name Name of the variable to search for.
 * @return Pointer to the found Variable; NULL if not found.
 */
Variable *find_variable(ScopeStack *stack, const char *name);

/*!
 * \brief Modifies the value of a variable in the ScopeStack.
 *
 * @param stack Pointer to the ScopeStack.
 * @param name Name of the variable to modify.
 * @param value_node New value node to assign to the variable.
 */
ASTNode *modify_variable_value(ScopeStack *memory, char *name, ASTNode *value_node);

/*!
 * \brief Prints the contents of the memory scopes.
 *
 * This function prints the details of variables stored in memory across different scopes.
 *
 * @param memory A pointer to the ScopeStack representing the memory scopes.
 */
void print_memory(const ScopeStack *memory);