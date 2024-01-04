#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

/*!
 * \brief Enumerates different node types in an Abstract Syntax Tree (AST).
 *
 * This enumeration represents various node types used in an Abstract Syntax Tree.
 * It includes identifiers, types, values, operators, delimiters, and helper nodes.
 */
typedef enum
{
    NODE_ID,         /**< Identifier (variable name) - 0 */
    NODE_V_TYPE,     /**< Variable type - 1 */
    NODE_VAL,        /**< Value (Variable value) - 2 */
    NODE_T_VAL,      /**< Text variable value (char/string) - 3 */
    NODE_KEYWORD,    /**< Keywords (e.g., SET, PRINT, IF, WHILE) - 4 */
    NODE_ARITH_OP,   /**< Arithmetic operators (e.g., +, -) - 5 */
    NODE_LOGIC_OP,   /**< Logic operators (e.g., ||, &&) - 6 */
    NODE_RELAT_OP,   /**< Relational operators (e.g., >, ==) - 7 */
    NODE_ASSIGN,     /**< Assignment operator (=) - 8 */
    NODE_O_BRACKET,  /**< Opening bracket { - 9 */
    NODE_C_BRACKET,  /**< Closing bracket } - 10 */
    NODE_LIST_B,     /**< Begining of the list [ - 11 */
    NODE_LIST_E,     /**< Ending of the list ] - 12 */
    NODE_O_PAREN,    /**< Opening parenthesis ( - 13 */
    NODE_C_PAREN,    /**< Closing parenthesis ) - 14 */
    NODE_R_TYPE,     /**< Return type -> - 15 */
    NODE_COMMA,      /**< Comma , - 16 */
    NODE_SEMI,       /**< Semicolon ; - 17 */
    NODE_ROOT,       /**< Root parent_node of the program - 18 */
    NODE_EXPRESSION, /**< Helper node to handle expressions - 19 */
    NODE_SCOPE,      /**< Helper node to handle code scopes - 20 */
    NODE_PARAMETERS, /**< Helper node to handle function parameters - 21 */
    NODE_RETURN,     /**< Helper node to handle function return - 22 */
    NODE_FUNC_CALL,  /**< Helper node to handle function calls - 23 */
    NODE_V_DEF,      /**< Helper node to handle variable definition - 24 */
    NODE_EOF,        /**< EOF node used to stop interpreting as success - 25 */
    NODE_ERROR       /**< Error node used to help with testing syntax errors - 26 */
} NodeType;

/*!
 * \brief Represents a node in an Abstract Syntax Tree (AST).
 *
 * This structure defines a node in an Abstract Syntax Tree.
 * It contains a NodeType indicating its type, a value (if applicable),
 * an array of child nodes, and the number of children.
 */
typedef struct ASTNode
{
    NodeType type;             /**< Type of the AST node */
    char *value;               /**< Value associated with the node */
    struct ASTNode **children; /**< Array of child nodes */
    size_t children_num;       /**< Number of children nodes */
} ASTNode;

/*!
 * \brief Prints the Abstract Syntax Tree (AST) rooted at 'root' node.
 *
 * This function prints the AST tree starting from the 'root' node recursively
 * with the given 'depth' for indentation.
 *
 * @param root Root node of the AST.
 * @param depth Depth of the node in the AST tree.
 */
void print_ASTree(ASTNode *root, int depth);

/*!
 * \brief Frees the memory allocated for the AST rooted at 'node'.
 *
 * This function traverses the AST rooted at 'node' recursively
 * and frees the memory allocated for each node and its children.
 *
 * @param node Root node of the AST to be freed.
 */
void free_ASTree(ASTNode *node);

/*!
 * \brief Creates a new ASTNode with the specified type and value.
 *
 * This function creates a new ASTNode with the given 'type' and 'value'.
 * It returns a pointer to the newly created node.
 *
 * @param type NodeType of the new node.
 * @param value Value associated with the new node.
 * @return Pointer to the newly created ASTNode.
 */
ASTNode *create_ASTNode(NodeType type, char *value);

/*!
 * \brief Adds a child node to the parent node in the AST.
 *
 * This function adds 'child' node to the list of children of 'parent' node in the AST.
 *
 * @param parent Parent node to which the 'child' node is added.
 * @param child Child node to be added.
 */
void add_child(ASTNode *parent, ASTNode *child);

/*!
 * \brief Creates a node representing a variable declaration.
 *
 * This function creates a node representing a variable declaration
 * with the specified 'type' and 'id' (identifier) and returns the created node.
 *
 * @param type Type of the variable being declared.
 * @param id Identifier (name) of the variable being declared.
 * @return Pointer to the newly created ASTNode representing the variable declaration.
 */
ASTNode *create_variable_declaration(const char *type, const char *id);

/*!
 * \brief Creates a node representing a literal value.
 *
 * This function creates a node representing a literal value
 * of the specified 'type' and 'value' and returns the created node.
 *
 * @param type NodeType indicating the type of the literal value.
 * @param value Value of the literal.
 * @return Pointer to the newly created ASTNode representing the literal value.
 */
ASTNode *create_literal(NodeType type, const char *value);

/*!
 * \brief Creates a node representing an assignment operation.
 *
 * This function creates a node representing an assignment operation
 * between 'variable' and 'expression' nodes and returns the created node.
 *
 * @param variable ASTNode representing the variable being assigned.
 * @param expression ASTNode representing the expression being assigned.
 * @return Pointer to the newly created ASTNode representing the assignment operation.
 */
ASTNode *create_assignment(ASTNode *variable, ASTNode *expression);

/*!
 * \brief Creates a node representing a print statement.
 *
 * This function creates a node representing a print statement
 * with the specified 'expression' and returns the created node.
 *
 * @param expression ASTNode representing the expression to be printed.
 * @return Pointer to the newly created ASTNode representing the print statement.
 */
ASTNode *create_print_statement(ASTNode *expression);

/*!
 * \brief Creates a node representing an if statement.
 *
 * This function creates a node representing an if statement
 * with the specified 'condition', 'if_body', and 'else_body' nodes and returns the created node.
 *
 * @param condition ASTNode representing the condition for the if statement.
 * @param if_body ASTNode representing the body of the if statement.
 * @param else_body ASTNode representing the body of the else statement (can be NULL for no else).
 * @return Pointer to the newly created ASTNode representing the if statement.
 */
ASTNode *create_if_statement(ASTNode *condition, ASTNode *if_body, ASTNode *else_body);

/*!
 * \brief Creates a node representing a while loop.
 *
 * This function creates a node representing a while loop
 * with the specified 'condition' and 'loop_body' nodes and returns the created node.
 *
 * @param condition ASTNode representing the condition for the while loop.
 * @param loop_body ASTNode representing the body of the while loop.
 * @return Pointer to the newly created ASTNode representing the while loop.
 */
ASTNode *create_while_loop(ASTNode *condition, ASTNode *loop_body);

/*!
 * \brief Creates a node representing a function declaration.
 *
 * This function creates a node representing a function declaration
 * with the specified 'name', 'return_type', 'parameter_list', and 'function_body' nodes and returns the created node.
 *
 * @param name Name of the function being declared.
 * @param return_type Return type of the function being declared.
 * @param parameter_list ASTNode representing the list of parameters for the function.
 * @param function_body ASTNode representing the body of the function.
 * @return Pointer to the newly created ASTNode representing the function declaration.
 */
ASTNode *create_function_declaration(const char *name, const char *return_type, ASTNode *parameter_list, ASTNode *function_body);

/*!
 * \brief Parses a program from the given tokens and constructs the Abstract Syntax Tree (AST).
 *
 * This function parses a program from the 'tokens' array and constructs the Abstract Syntax Tree (AST).
 * It returns the root node of the AST representing the parsed program.
 *
 * @param tokens Array of tokens representing the program.
 * @return Pointer to the root node of the constructed AST.
 */
ASTNode *parse_program(Token **tokens);
