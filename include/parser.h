#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

// Token types
typedef enum
{
    NODE_ID,         // 0 Identifier (variable name)
    NODE_V_TYPE,     // 1 Variable type
    NODE_VAL,        // 2 Value (Variable value)
    NODE_T_VAL,      // 3 Text variable value (char/string)
    NODE_KEYWORD,    // 4 Keywords (e.g., SET, PRINT, IF, WHILE)
    NODE_ARITH_OP,   // 5 Arithmetic operators (e.g., +, -)
    NODE_LOGIC_OP,   // 6 Logic operators (e.g., ||, &&)
    NODE_RELAT_OP,   // 7 Relational operators (e.g., >, ==)
    NODE_ASSIGN,     // 8 Assignment operator (=)
    NODE_O_BRACKET,  // 9 Opening bracket {
    NODE_C_BRACKET,  // 10 Closing bracket }
    NODE_LIST_B,     // 11 Begining of the list [
    NODE_LIST_E,     // 12 Ending of the list ]
    NODE_O_PAREN,    // 13 Opening parenthesis (
    NODE_C_PAREN,    // 14 Closing parenthesis )
    NODE_R_TYPE,     // 15 Return type ->
    NODE_COMMA,      // 16 Comma ,
    NODE_SEMI,       // 17 Semicolon ;
    NODE_ROOT,       // 18 Root parent_node of the program
    NODE_EXPRESSION, // 19 Helper node to handle expressions
    NODE_SCOPE,      // 20 Helper node to handle code scopes
    NODE_PARAMETERS  // 21 Helper node to handle function parameters
} NodeType;

// Define the ASTNode structure
typedef struct ASTNode
{
    NodeType type;
    char *value;
    struct ASTNode **children;
    size_t children_num;
} ASTNode;

// Function to print AST
void print_ASTree(ASTNode *root, int depth);
// Function to free ASTree
void free_ASTree(ASTNode *node);

// Function to create a new ASTNode
ASTNode *create_ASTNode(NodeType type, char *value);

// Function to add a child node to a parent node
void add_child(ASTNode *parent, ASTNode *child);

// Declaration of other functions used in the code
ASTNode *create_variable_declaration(const char *type, const char *id);
ASTNode *create_literal(NodeType type, const char *value);
ASTNode *create_assignment(ASTNode *variable, ASTNode *expression);
ASTNode *create_print_statement(ASTNode *expression);
ASTNode *create_if_statement(ASTNode *condition, ASTNode *if_body, ASTNode *else_body);
ASTNode *create_while_loop(ASTNode *condition, ASTNode *loop_body);
ASTNode *create_function_declaration(const char *name, const char *return_type, ASTNode *parameter_list, ASTNode *function_body);
ASTNode *generate_expressionTree(ASTNode *expression);
ASTNode *parse_program(Token **tokens);
