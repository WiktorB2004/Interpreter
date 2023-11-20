#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

// Function to print AST
void print_ASTree(ASTNode *root, int depth)
{
    if (root == NULL)
    {
        return;
    }

    for (int i = 0; i < depth; ++i)
    {
        printf("  ");
    }

    printf("(%d) %s -> [%ld] \n", root->type, root->value, root->children_num);

    for (size_t i = 0; i < root->children_num; ++i)
    {
        print_ASTree(root->children[i], depth + 1);
    }
}

// Function to create a new ASTNode
ASTNode *create_ASTNode(NodeType type, char *value)
{
    ASTNode *newNode = (ASTNode *)malloc(sizeof(ASTNode));
    if (newNode != NULL)
    {
        newNode->type = type;
        newNode->value = strdup(value);
        newNode->children = NULL;
        newNode->children_num = 0;
    }
    return newNode;
}

// Function to add a child parent_node to a parent parent_node
void add_child(ASTNode *parent, ASTNode *child)
{
    parent->children = realloc(parent->children, (parent->children_num + 1) * sizeof(ASTNode *));
    if (parent->children != NULL)
    {
        parent->children[parent->children_num++] = child;
    }
    else
    {
        fprintf(stderr, "Memory allocation failed for adding child.\n");
        exit(EXIT_FAILURE);
    }
}

ASTNode *create_variable_declaration(const char *type, const char *id)
{
}

ASTNode *create_literal(NodeType type, const char *value)
{
}

ASTNode *create_assignment(ASTNode *variable, ASTNode *expression)
{
    ASTNode *assignment_node = (ASTNode *)malloc(sizeof(ASTNode));
    if (assignment_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    assignment_node->type = NODE_ASSIGN;
    assignment_node->value = "Assignment";
    assignment_node->children_num = 2;
    assignment_node->children = (ASTNode **)malloc(sizeof(ASTNode *) * assignment_node->children_num);
    if (assignment_node->children == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    assignment_node->children[0] = variable;
    assignment_node->children[1] = expression;

    return assignment_node;
}

ASTNode *create_print_statement(ASTNode *expression)
{
}

ASTNode *create_if_statement(ASTNode *condition, ASTNode *if_body, ASTNode *else_body)
{
}

ASTNode *create_while_loop(ASTNode *condition, ASTNode *loop_body)
{
}

ASTNode *create_function_declaration(const char *name, const char *return_type, ASTNode *parameter_list, ASTNode *function_body)
{
}

void expression_to_expressionTree(ASTNode *expression)
{
}

ASTNode *
parse_program(Token **tokens)
{
    ASTNode *root = create_ASTNode(NODE_ROOT, "ROOT");
    ASTNode *parent_node = root;
    Token *token = *tokens;
    int line_count = 1;
    if (!root)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    while (token->type != TOKEN_EOF)
    {
        if (token->type == TOKEN_Newline)
        {
            line_count++;
        }
        else
        {
            if (token->type == ID)
            {
                ASTNode *id, *expression;
                id = create_ASTNode(NODE_ID, token->value);
                *token++;
                if (token->type == ASSIGN)
                {
                    *token++;
                    // ASSIGNING TEXT VALUE
                    if (token->type == T_VAL)
                    {
                        add_child(parent_node, create_assignment(id, create_ASTNode(NODE_T_VAL, token->value)));
                        *token++;
                    }
                    else
                    {
                        // HANDLE THE EXPRESSION OR NORMAL VALUE ASSIGNMENT
                        expression = create_ASTNode(NODE_EXPRESSION, "expression");
                        while (token->type != SEMI && token->type != TOKEN_Newline)
                        {
                            if (token->type == ARITH_OP)
                            {
                                add_child(expression, create_ASTNode(NODE_ARITH_OP, token->value));
                            }
                            else if (token->type == RELAT_OP)
                            {
                                add_child(expression, create_ASTNode(NODE_RELAT_OP, token->value));
                            }
                            else if (token->type == VAL)
                            {
                                add_child(expression, create_ASTNode(NODE_VAL, token->value));
                            }
                            else
                            {
                                fprintf(stderr, "Incorrect token occured on %d line\n", line_count);
                                // exit(EXIT_FAILURE);
                                break;
                            }
                            *token++;
                        }
                        // expression_to_expressionTree(expression);
                        add_child(parent_node, create_assignment(id, expression));
                    }
                    if (token->type != SEMI)
                    {
                        fprintf(stderr, "Missing semicolon on line %d\n", line_count);
                        // exit(EXIT_FAILURE);
                    }
                }
                else
                {
                    fprintf(stderr, "Incorrect token occured after variable id on line %d.\n", line_count);
                    // exit(EXIT_FAILURE);
                }
            }
            else if (token->type == V_TYPE)
            {
            }
            else if (token->type == KEYWORD)
            {
            }
            else if (token->type == O_BRACKET)
            {
            }
            else
            {
                fprintf(stderr, "Invalid token %s : %d (Value:Type) on line %d\n", token->value, token->type, line_count);
                // exit(EXIT_FAILURE);
            }
        }
        *token++;
    }

    return root;
}