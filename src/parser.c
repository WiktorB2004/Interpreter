#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../include/utils/ASTNode_Stack.h"

// FIXME: Reafactor the code - move logic into prepared functions
// FIXME: Test the code - write automated test cases for parser and lexer + create good/bad example files
// FIXME: Comment the code and document the logic

// Function to print AST
void print_ASTree(ASTNode *root, int depth)
{
    if (root == NULL)
    {
        return;
    }

    printf("|");
    for (int i = 0; i < depth; ++i)
    {
        printf("-- ");
    }
    printf("|");

    printf("(%d) %s -> [%ld]\n", root->type, root->value, root->children_num);

    for (size_t i = 0; i < root->children_num; ++i)
    {
        print_ASTree(root->children[i], depth + 1);
    }
}

// BUG: free: invalid pointer - smth with children
void free_ASTree(ASTNode *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->value != NULL)
    {
        free(node->value);
    }
    if (node->children != NULL)
    {
        for (size_t i = 0; i < node->children_num; i++)
        {
            free_ASTree(node->children[i]);
        }
        free(node->children);
    }

    free(node);
}
// Function to create a new ASTNode
ASTNode *create_ASTNode(NodeType type, char *value)
{
    ASTNode *newNode = (ASTNode *)malloc(sizeof(ASTNode));
    if (newNode != NULL && value != NULL)
    {
        newNode->type = type;
        newNode->value = strdup(value);
        newNode->children = NULL;
        newNode->children_num = 0;
    }
    else
    {
        fprintf(stderr, "Memory allocation failed for creating ASTNode.\n");
        exit(EXIT_FAILURE);
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

ASTNode *parse_program(Token **tokens)
{
    ASTNode *parent_node, *root = create_ASTNode(NODE_ROOT, "ROOT");
    ASTNodeStack *root_stack = create_ASTNodeStack();
    ASTNodeStack_push(root_stack, root);
    Token *token = *tokens;
    int line_count = 1;

    while (token->type != TOKEN_EOF)
    {
        parent_node = ASTNodeStack_peek(root_stack);
        if (token->type == TOKEN_Newline)
        {
            line_count++;
        }
        else
        {
            if (token->type == ID)
            {
                ASTNode *id;
                id = create_ASTNode(NODE_ID, token->value);
                *token++;
                if (token->type == ASSIGN)
                {
                    *token++;
                    if (token->type == T_VAL)
                    {
                        add_child(parent_node, create_assignment(id, create_ASTNode(NODE_T_VAL, token->value)));
                        *token++;
                    }
                    else if (token->type == LIST_B)
                    {
                        ASTNode *list = create_ASTNode(NODE_LIST_B, "List");
                        *token++;
                        while (token->type != LIST_E && token->type != TOKEN_Newline)
                        {
                            if (token->type != COMMA)
                            {
                                switch (token->type)
                                {
                                case VAL:
                                    add_child(list, create_ASTNode(NODE_VAL, token->value));
                                    break;
                                case T_VAL:
                                    add_child(list, create_ASTNode(NODE_T_VAL, token->value));
                                    break;
                                default:
                                    fprintf(stderr, "Incorrect list declaration on %d line\n", line_count);
                                    exit(EXIT_FAILURE);
                                    break;
                                }
                            }
                            *token++;
                        }
                        if (token->type != LIST_E)
                        {
                            fprintf(stderr, "Expected ] after opening the list on %d line\n", line_count);
                            exit(EXIT_FAILURE);
                        }
                        add_child(parent_node, create_assignment(id, list));
                        *token++;
                    }
                    else
                    {
                        ASTNode *expression = create_ASTNode(NODE_EXPRESSION, "Expression");
                        while (token->type != SEMI && token->type != TOKEN_Newline)
                        {
                            switch (token->type)
                            {
                            case ARITH_OP:
                                add_child(expression, create_ASTNode(NODE_ARITH_OP, token->value));
                                break;
                            case RELAT_OP:
                                add_child(expression, create_ASTNode(NODE_RELAT_OP, token->value));
                                break;
                            case LOGIC_OP:
                                add_child(expression, create_ASTNode(NODE_LOGIC_OP, token->value));
                                break;
                            case VAL:
                                add_child(expression, create_ASTNode(NODE_VAL, token->value));
                                break;
                            case ID:
                                add_child(expression, create_ASTNode(NODE_ID, token->value));
                                break;
                            case O_PAREN:
                                add_child(expression, create_ASTNode(NODE_O_PAREN, token->value));
                                break;
                            case C_PAREN:
                                add_child(expression, create_ASTNode(NODE_C_PAREN, token->value));
                                break;
                            default:
                                fprintf(stderr, "Incorrect token occured on %d line\n", line_count);
                                exit(EXIT_FAILURE);
                                break;
                            }
                            *token++;
                        }
                        add_child(parent_node, create_assignment(id, expression));
                    }
                    if (token->type != SEMI)
                    {
                        fprintf(stderr, "Expected semicolon on line %d\n", line_count);
                        exit(EXIT_FAILURE);
                    }
                }
                else if (token->type == O_PAREN)
                {
                    *token++;
                    ASTNode *function_call = create_ASTNode(NODE_FUNC_CALL, "Function_Call");
                    add_child(function_call, create_ASTNode(NODE_ID, id->value));
                    ASTNode *parameter_list = create_ASTNode(NODE_PARAMETERS, "Function_Parameters");
                    while (token->type != C_PAREN && token->type != TOKEN_Newline)
                    {
                        if (token->type != COMMA)
                        {
                            switch (token->type)
                            {
                            case ID:
                                add_child(parameter_list, create_ASTNode(NODE_ID, token->value));
                                break;
                            case VAL:
                                add_child(parameter_list, create_ASTNode(NODE_VAL, token->value));
                                break;
                            case T_VAL:
                                add_child(parameter_list, create_ASTNode(NODE_T_VAL, token->value));
                                break;
                            default:
                                fprintf(stderr, "Invalid parameters provided in function call on line: %d.\n", line_count);
                                exit(EXIT_FAILURE);
                                break;
                            }
                        }
                        *token++;
                    }
                    *token++;
                    if (token->type != SEMI)
                    {
                        fprintf(stderr, "Missing semicolon on line: %d.\n", line_count);
                        exit(EXIT_FAILURE);
                    }
                    add_child(function_call, parameter_list);
                    add_child(parent_node, function_call);
                }
                else
                {

                    fprintf(stderr, "Incorrect token occured after variable id on line %d.\n", line_count);
                    exit(EXIT_FAILURE);
                }
            }
            else if (token->type == V_TYPE)
            {
                ASTNode *variable = create_ASTNode(NODE_V_DEF, "Variable_Declaration");
                add_child(variable, create_ASTNode(NODE_V_TYPE, token->value));
                *token++;
                if (token->type == ID)
                {
                    add_child(variable, create_ASTNode(NODE_ID, token->value));
                    *token++;
                    if (token->type == ASSIGN)
                    {
                        *token++;
                        if (token->type == T_VAL)
                        {
                            ASTNode *expression = create_ASTNode(NODE_EXPRESSION, "Value");
                            add_child(expression, create_ASTNode(NODE_T_VAL, token->value));
                            add_child(variable, expression);
                            add_child(parent_node, variable);
                            *token++;
                        }
                        else if (token->type == LIST_B)
                        {
                            ASTNode *list = create_ASTNode(NODE_LIST_B, "List");
                            *token++;
                            while (token->type != LIST_E && token->type != TOKEN_Newline)
                            {
                                if (token->type != COMMA)
                                {
                                    switch (token->type)
                                    {
                                    case VAL:
                                        add_child(list, create_ASTNode(NODE_VAL, token->value));
                                        break;
                                    case T_VAL:
                                        add_child(list, create_ASTNode(NODE_T_VAL, token->value));
                                        break;
                                    default:
                                        fprintf(stderr, "Incorrect list declaration on %d line\n", line_count);
                                        exit(EXIT_FAILURE);
                                        break;
                                    }
                                }
                                *token++;
                            }
                            if (token->type != LIST_E)
                            {
                                fprintf(stderr, "Expected ] after opening the list on %d line\n", line_count);
                                exit(EXIT_FAILURE);
                            }
                            add_child(variable, list);
                            add_child(parent_node, variable);
                            *token++;
                        }
                        else if (token->type == ID)
                        {
                            char *identifier = token->value;
                            *token++;
                            if (token->type == SEMI)
                            {
                                add_child(variable, create_ASTNode(NODE_ID, identifier));
                            }
                            else if (token->type == O_PAREN)
                            {
                                *token++;
                                ASTNode *function_call = create_ASTNode(NODE_FUNC_CALL, "Function_Call");
                                add_child(function_call, create_ASTNode(NODE_ID, identifier));
                                ASTNode *parameter_list = create_ASTNode(NODE_PARAMETERS, "Function_Parameters");
                                while (token->type != C_PAREN && token->type != TOKEN_Newline)
                                {
                                    if (token->type != COMMA)
                                    {
                                        switch (token->type)
                                        {
                                        case ID:
                                            add_child(parameter_list, create_ASTNode(NODE_ID, token->value));
                                            break;
                                        case VAL:
                                            add_child(parameter_list, create_ASTNode(NODE_VAL, token->value));
                                            break;
                                        case T_VAL:
                                            add_child(parameter_list, create_ASTNode(NODE_T_VAL, token->value));
                                            break;
                                        default:
                                            fprintf(stderr, "Invalid parameters provided in function call on line: %d.\n", line_count);
                                            exit(EXIT_FAILURE);
                                            break;
                                        }
                                    }
                                    *token++;
                                }
                                add_child(function_call, parameter_list);
                                add_child(variable, function_call);
                                add_child(parent_node, variable);
                                *token++;
                            }
                            else
                            {
                                *token--;
                                ASTNode *expression = create_ASTNode(NODE_EXPRESSION, "Expression");
                                while (token->type != SEMI && token->type != TOKEN_Newline)
                                {
                                    switch (token->type)
                                    {
                                    case ARITH_OP:
                                        add_child(expression, create_ASTNode(NODE_ARITH_OP, token->value));
                                        break;
                                    case RELAT_OP:
                                        add_child(expression, create_ASTNode(NODE_RELAT_OP, token->value));
                                        break;
                                    case LOGIC_OP:
                                        add_child(expression, create_ASTNode(NODE_LOGIC_OP, token->value));
                                        break;
                                    case VAL:
                                        add_child(expression, create_ASTNode(NODE_VAL, token->value));
                                        break;
                                    case ID:
                                        add_child(expression, create_ASTNode(NODE_ID, token->value));
                                        break;
                                    case O_PAREN:
                                        add_child(expression, create_ASTNode(NODE_O_PAREN, token->value));
                                        break;
                                    case C_PAREN:
                                        add_child(expression, create_ASTNode(NODE_C_PAREN, token->value));
                                        break;
                                    default:
                                        fprintf(stderr, "Incorrect token occured on %d line\n", line_count);
                                        exit(EXIT_FAILURE);
                                        break;
                                    }
                                    *token++;
                                }
                                add_child(variable, expression);
                                add_child(parent_node, variable);
                            }
                        }
                        else
                        {
                            ASTNode *expression = create_ASTNode(NODE_EXPRESSION, "Expression");
                            while (token->type != SEMI && token->type != TOKEN_Newline)
                            {
                                switch (token->type)
                                {
                                case ARITH_OP:
                                    add_child(expression, create_ASTNode(NODE_ARITH_OP, token->value));
                                    break;
                                case RELAT_OP:
                                    add_child(expression, create_ASTNode(NODE_RELAT_OP, token->value));
                                    break;
                                case LOGIC_OP:
                                    add_child(expression, create_ASTNode(NODE_LOGIC_OP, token->value));
                                    break;
                                case VAL:
                                    add_child(expression, create_ASTNode(NODE_VAL, token->value));
                                    break;
                                case ID:
                                    add_child(expression, create_ASTNode(NODE_ID, token->value));
                                    break;
                                case O_PAREN:
                                    add_child(expression, create_ASTNode(NODE_O_PAREN, token->value));
                                    break;
                                case C_PAREN:
                                    add_child(expression, create_ASTNode(NODE_C_PAREN, token->value));
                                    break;
                                default:
                                    fprintf(stderr, "Incorrect token occured on %d line\n", line_count);
                                    exit(EXIT_FAILURE);
                                    break;
                                }
                                *token++;
                            }
                            add_child(variable, expression);
                            add_child(parent_node, variable);
                        }
                        if (token->type != SEMI)
                        {
                            printf("%s", token->value);
                            fprintf(stderr, "Expected semicolon on line %d\n", line_count);
                            exit(EXIT_FAILURE);
                        }
                    }
                    else
                    {
                        fprintf(stderr, "Incorrect variable definition on line %d.\n", line_count);
                        exit(EXIT_FAILURE);
                    }
                }
                else
                {
                    fprintf(stderr, "Incorrect variable definition on line %d.\n", line_count);
                    exit(EXIT_FAILURE);
                }
            }
            else if (token->type == KEYWORD)
            {
                if (strcmp(token->value, "DEF") == 0)
                {
                    ASTNode *scope = create_ASTNode(NODE_SCOPE, "Function_Scope");
                    *token++;
                    if (token->type == ID)
                    {
                        add_child(scope, create_ASTNode(NODE_ID, token->value));
                        *token++;
                        if (token->type == R_TYPE)
                        {
                            *token++;
                            if (token->type == V_TYPE)
                            {
                                add_child(scope, create_ASTNode(NODE_R_TYPE, token->value));
                                *token++;
                                if (token->type == O_PAREN)
                                {
                                    ASTNode *parameters_list = create_ASTNode(NODE_PARAMETERS, "Parameters_List");
                                    *token++;
                                    while (token->type != C_PAREN & token->type != TOKEN_Newline)
                                    {
                                        if (token->type != COMMA)
                                        {
                                            if (token->type == ID)
                                            {
                                                add_child(parameters_list, create_ASTNode(NODE_ID, token->value));
                                            }
                                            else
                                            {
                                                fprintf(stderr, "Invalid parameters provided in function declaration on line: %d.\n", line_count);
                                                exit(EXIT_FAILURE);
                                            }
                                        }
                                        *token++;
                                    }
                                    if (token->type == C_PAREN)
                                    {
                                        add_child(scope, parameters_list);
                                        *token++;
                                    }
                                    else
                                    {
                                        fprintf(stderr, "Incorrect function definition, missing closing parenthese on line: %d.\n", line_count);
                                        exit(EXIT_FAILURE);
                                    }
                                }
                                else
                                {
                                    fprintf(stderr, "Incorrect function definition, missing parentheses on line: %d.\n", line_count);
                                    exit(EXIT_FAILURE);
                                }
                            }
                            else
                            {
                                fprintf(stderr, "Incorrect function definition, incorrect identifier on line: %d.\n", line_count);
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                    else
                    {
                        fprintf(stderr, "Return type not specified on line: %d.\n", line_count);
                        exit(EXIT_FAILURE);
                    }
                    ASTNode *function_body = create_ASTNode(NODE_SCOPE, "Function_Body");
                    ASTNodeStack_push(root_stack, scope);
                    ASTNodeStack_push(root_stack, function_body);
                }
                // FIXME: Make it handle funtion return value print
                else if (strcmp(token->value, "PRINT") == 0)
                {
                    ASTNode *print_statement = create_ASTNode(NODE_KEYWORD, "Print");
                    *token++;
                    if (token->type == T_VAL)
                    {
                        add_child(print_statement, create_ASTNode(NODE_T_VAL, token->value));
                        *token++;
                        if (token->type != SEMI)
                        {
                            fprintf(stderr, "Missing semicolon on line: %d.\n", line_count);
                            exit(EXIT_FAILURE);
                        }
                    }
                    else if (token->type == VAL)
                    {
                        ASTNode *expression = create_ASTNode(NODE_EXPRESSION, "Print_Expression");
                        while (token->type != SEMI && token->type != TOKEN_Newline)
                        {
                            switch (token->type)
                            {
                            case VAL:
                                add_child(expression, create_ASTNode(NODE_VAL, token->value));
                                break;
                            case ID:
                                add_child(expression, create_ASTNode(NODE_ID, token->value));
                                break;
                            case ARITH_OP:
                                add_child(expression, create_ASTNode(NODE_ARITH_OP, token->value));
                                break;
                            case NODE_LOGIC_OP:
                                add_child(expression, create_ASTNode(NODE_LOGIC_OP, token->value));
                                break;
                            case RELAT_OP:
                                add_child(expression, create_ASTNode(NODE_RELAT_OP, token->value));
                                break;
                            default:
                                fprintf(stderr, "Invalid token inside print expression on line: %d.\n", line_count);
                                exit(EXIT_FAILURE);
                                break;
                            }
                            *token++;
                        }
                        if (token->type != SEMI)
                        {
                            fprintf(stderr, "Missing semicolon on line: %d.\n", line_count);
                            exit(EXIT_FAILURE);
                        }
                        add_child(print_statement, expression);
                    }
                    else if (token->type == ID)
                    {
                        char *identifier = token->value;
                        *token++;
                        if (token->type == SEMI)
                        {
                            add_child(print_statement, create_ASTNode(NODE_ID, identifier));
                        }
                        else if (token->type == O_PAREN)
                        {
                            *token++;
                            ASTNode *function_call = create_ASTNode(NODE_FUNC_CALL, "Function_Call");
                            add_child(function_call, create_ASTNode(NODE_ID, identifier));
                            ASTNode *parameter_list = create_ASTNode(NODE_PARAMETERS, "Function_Parameters");
                            while (token->type != C_PAREN)
                            {
                                if (token->type != COMMA)
                                {
                                    switch (token->type)
                                    {
                                    case ID:
                                        add_child(parameter_list, create_ASTNode(NODE_ID, token->value));
                                        break;
                                    case VAL:
                                        add_child(parameter_list, create_ASTNode(NODE_VAL, token->value));
                                        break;
                                    case T_VAL:
                                        add_child(parameter_list, create_ASTNode(NODE_T_VAL, token->value));
                                        break;
                                    default:
                                        fprintf(stderr, "Invalid parameters provided in function call on line: %d.\n", line_count);
                                        exit(EXIT_FAILURE);
                                        break;
                                    }
                                }
                                *token++;
                            }
                            *token++;
                            if (token->type != SEMI)
                            {
                                fprintf(stderr, "Missing semicolon on line: %d.\n", line_count);
                                exit(EXIT_FAILURE);
                            }
                            add_child(function_call, parameter_list);
                            add_child(print_statement, function_call);
                        }
                    }
                    else if (token->type == LIST_B)
                    {
                        ASTNode *list = create_ASTNode(NODE_LIST_B, "List");
                        *token++;
                        while (token->type != LIST_E && token->type != TOKEN_Newline)
                        {
                            if (token->type != COMMA)
                            {
                                switch (token->type)
                                {
                                case VAL:
                                    add_child(list, create_ASTNode(NODE_VAL, token->value));
                                    break;
                                case T_VAL:
                                    add_child(list, create_ASTNode(NODE_T_VAL, token->value));
                                    break;
                                default:
                                    fprintf(stderr, "Incorrect list declaration on %d line\n", line_count);
                                    exit(EXIT_FAILURE);
                                    break;
                                }
                            }
                            *token++;
                        }
                        if (token->type != LIST_E)
                        {
                            fprintf(stderr, "Expected ] after opening the list on %d line\n", line_count);
                            exit(EXIT_FAILURE);
                        }
                        add_child(print_statement, list);
                        *token++;
                    }
                    else
                    {
                        fprintf(stderr, "Invalid print parameter on line: %d.\n", line_count);
                        exit(EXIT_FAILURE);
                    }
                    add_child(parent_node, print_statement);
                }
                else if (strcmp(token->value, "WHILE") == 0)
                {
                    ASTNode *scope = create_ASTNode(NODE_SCOPE, "While_Loop");
                    ASTNode *conditions = create_ASTNode(NODE_EXPRESSION, "Conditions");
                    *token++;
                    if (token->type == O_PAREN)
                    {
                        *token++;
                        while (token->type != C_PAREN && token->type != TOKEN_Newline)
                        {
                            switch (token->type)
                            {
                            case VAL:
                                add_child(conditions, create_ASTNode(NODE_VAL, token->value));
                                break;
                            case ID:
                                add_child(conditions, create_ASTNode(NODE_ID, token->value));
                                break;
                            case T_VAL:
                                add_child(conditions, create_ASTNode(NODE_T_VAL, token->value));
                                break;
                            case ARITH_OP:
                                add_child(conditions, create_ASTNode(NODE_ARITH_OP, token->value));
                                break;
                            case RELAT_OP:
                                add_child(conditions, create_ASTNode(NODE_RELAT_OP, token->value));
                                break;
                            case LOGIC_OP:
                                add_child(conditions, create_ASTNode(NODE_LOGIC_OP, token->value));
                                break;
                            default:
                                fprintf(stderr, "Invalid token inside WHILE conditions on line: %d.\n", line_count);
                                exit(EXIT_FAILURE);
                                break;
                            }
                            *token++;
                        }
                        *token++;
                        if (token->type != O_BRACKET)
                        {
                            fprintf(stderr, "Missing { after while condition on line: %d.\n", line_count);
                            exit(EXIT_FAILURE);
                        }
                    }
                    else
                    {
                        fprintf(stderr, "Invalid token inside IF statement on line: %d.\n", line_count);
                        exit(EXIT_FAILURE);
                    }
                    add_child(scope, conditions);
                    ASTNode *body = create_ASTNode(NODE_SCOPE, "Loop_Body");
                    ASTNodeStack_push(root_stack, scope);
                    ASTNodeStack_push(root_stack, body);
                }
                else if (strcmp(token->value, "IF") == 0)
                {
                    *token++;
                    if (token->type == O_PAREN)
                    {
                        *token++;
                        ASTNode *scope = create_ASTNode(NODE_SCOPE, "Conditional_Scope");
                        ASTNode *conditions = create_ASTNode(NODE_EXPRESSION, "Conditions");
                        while (token->type != C_PAREN && token->type != TOKEN_Newline)
                        {
                            switch (token->type)
                            {
                            case VAL:
                                add_child(conditions, create_ASTNode(NODE_VAL, token->value));
                                break;
                            case ID:
                                add_child(conditions, create_ASTNode(NODE_ID, token->value));
                                break;
                            case T_VAL:
                                add_child(conditions, create_ASTNode(NODE_T_VAL, token->value));
                                break;
                            case ARITH_OP:
                                add_child(conditions, create_ASTNode(NODE_ARITH_OP, token->value));
                                break;
                            case RELAT_OP:
                                add_child(conditions, create_ASTNode(NODE_RELAT_OP, token->value));
                                break;
                            case LOGIC_OP:
                                add_child(conditions, create_ASTNode(NODE_LOGIC_OP, token->value));
                                break;
                            default:
                                fprintf(stderr, "Invalid token inside IF statement on line: %d.\n", line_count);
                                exit(EXIT_FAILURE);
                                break;
                            }
                            *token++;
                        }
                        *token++;
                        if (token->type == O_BRACKET)
                        {
                            ASTNode *if_body = create_ASTNode(NODE_SCOPE, "If_Body");
                            add_child(scope, conditions);
                            ASTNodeStack_push(root_stack, scope);
                            ASTNodeStack_push(root_stack, if_body);
                        }
                        else
                        {
                            fprintf(stderr, "Invalid use of IF, missing { on line: %d.\n", line_count);
                            exit(EXIT_FAILURE);
                        }
                    }
                    else
                    {
                        fprintf(stderr, "Invalid use of IF on line: %d.\n", line_count);
                        exit(EXIT_FAILURE);
                    }
                }
                else if (strcmp(token->value, "ELSE") == 0)
                {
                    if (strcmp(parent_node->value, "If_Body") == 0)
                    {
                        ASTNodeStack_push(root_stack, create_ASTNode(NODE_SCOPE, "Else_Body"));
                    }
                    else
                    {
                        fprintf(stderr, "Invalid use of ELSE, missing preceding IF on line: %d.\n", line_count);
                        exit(EXIT_FAILURE);
                    }
                }
                else if (strcmp(token->value, "return") == 0)
                {
                    ASTNode *return_statement = create_ASTNode(NODE_RETURN, "Return_Statement");
                    *token++;
                    if (token->type == ID)
                    {
                        char *identifier = token->value;
                        *token++;
                        if (token->type == SEMI)
                        {
                            add_child(return_statement, create_ASTNode(NODE_ID, identifier));
                        }
                        else if (token->type == O_PAREN)
                        {
                            *token++;
                            ASTNode *function_call = create_ASTNode(NODE_FUNC_CALL, "Function_Call");
                            add_child(function_call, create_ASTNode(NODE_ID, identifier));
                            ASTNode *parameter_list = create_ASTNode(NODE_PARAMETERS, "Function_Parameters");
                            while (token->type != C_PAREN && token->type != TOKEN_Newline)
                            {
                                if (token->type != COMMA)
                                {
                                    switch (token->type)
                                    {
                                    case ID:
                                        add_child(parameter_list, create_ASTNode(NODE_ID, token->value));
                                        break;
                                    case VAL:
                                        add_child(parameter_list, create_ASTNode(NODE_VAL, token->value));
                                        break;
                                    case T_VAL:
                                        add_child(parameter_list, create_ASTNode(NODE_T_VAL, token->value));
                                        break;
                                    default:
                                        fprintf(stderr, "Invalid parameters provided in function call on line: %d.\n", line_count);
                                        exit(EXIT_FAILURE);
                                        break;
                                    }
                                }
                                *token++;
                            }
                            add_child(function_call, parameter_list);
                            add_child(return_statement, function_call);
                            *token++;
                        }
                        else
                        {
                            ASTNode *expression = create_ASTNode(NODE_EXPRESSION, "Return_Expression");
                            add_child(expression, create_ASTNode(NODE_ID, identifier));
                            while (token->type != SEMI && token->type != TOKEN_Newline)
                            {
                                switch (token->type)
                                {
                                case VAL:
                                    add_child(expression, create_ASTNode(NODE_VAL, token->value));
                                    break;
                                case ID:
                                    add_child(expression, create_ASTNode(NODE_ID, token->value));
                                    break;
                                case ARITH_OP:
                                    add_child(expression, create_ASTNode(NODE_ARITH_OP, token->value));
                                    break;
                                case NODE_LOGIC_OP:
                                    add_child(expression, create_ASTNode(NODE_LOGIC_OP, token->value));
                                    break;
                                case RELAT_OP:
                                    add_child(expression, create_ASTNode(NODE_RELAT_OP, token->value));
                                    break;
                                default:
                                    fprintf(stderr, "Invalid token inside print expression on line: %d.\n", line_count);
                                    exit(EXIT_FAILURE);
                                    break;
                                }
                                *token++;
                            }
                            add_child(return_statement, expression);
                        }
                    }
                    else if (token->type == VAL)
                    {
                        ASTNode *expression = create_ASTNode(NODE_EXPRESSION, "Return_Expression");
                        while (token->type != SEMI && token->type != TOKEN_Newline)
                        {
                            switch (token->type)
                            {
                            case VAL:
                                add_child(expression, create_ASTNode(NODE_VAL, token->value));
                                break;
                            case ID:
                                add_child(expression, create_ASTNode(NODE_ID, token->value));
                                break;
                            case ARITH_OP:
                                add_child(expression, create_ASTNode(NODE_ARITH_OP, token->value));
                                break;
                            case NODE_LOGIC_OP:
                                add_child(expression, create_ASTNode(NODE_LOGIC_OP, token->value));
                                break;
                            case RELAT_OP:
                                add_child(expression, create_ASTNode(NODE_RELAT_OP, token->value));
                                break;
                            default:
                                fprintf(stderr, "Invalid token inside print expression on line: %d.\n", line_count);
                                exit(EXIT_FAILURE);
                                break;
                            }
                            *token++;
                        }
                        add_child(return_statement, expression);
                    }
                    else if (token->type == T_VAL)
                    {
                        add_child(return_statement, create_ASTNode(NODE_T_VAL, token->value));
                        *token++;
                    }
                    ASTNode *tmp = ASTNodeStack_pop(root_stack);
                    char *func_name = ASTNodeStack_peek(root_stack)->children[0]->value;
                    add_child(return_statement, create_ASTNode(NODE_ID, func_name));
                    ASTNodeStack_push(root_stack, tmp);
                    add_child(parent_node, return_statement);
                    if (token->type != SEMI)
                    {
                        fprintf(stderr, "Missing semicolon on line: %d.\n", line_count);
                        exit(EXIT_FAILURE);
                    }
                }
            }
            else if (token->type == O_BRACKET)
            {
                if (strcmp(parent_node->value, "Function_Body") == 0 || strcmp(parent_node->value, "User_Scope") == 0)
                {
                    ASTNodeStack_push(root_stack, create_ASTNode(NODE_SCOPE, "User_Scope"));
                }
                else if (strcmp(parent_node->value, "Else_Body") != 0)
                {
                    fprintf(stderr, "Invalid Scope creation on line: %d.\n", line_count);
                    exit(EXIT_FAILURE);
                }
            }
            else if (token->type == C_BRACKET)
            {
                if (strcmp(parent_node->value, "If_Body") == 0)
                {
                    *token++;
                    if (strcmp(token->value, "ELSE") != 0)
                    {
                        ASTNode *if_body = ASTNodeStack_pop(root_stack);
                        ASTNode *if_scope = ASTNodeStack_pop(root_stack);
                        add_child(if_scope, if_body);
                        add_child(ASTNodeStack_peek(root_stack), if_scope);
                    }
                    else if (token->type == TOKEN_Newline)
                    {
                        *token++;
                        if (strcmp(token->value, "ELSE") != 0)
                        {
                            ASTNode *if_body = ASTNodeStack_pop(root_stack);
                            ASTNode *if_scope = ASTNodeStack_pop(root_stack);
                            add_child(if_scope, if_body);
                            add_child(ASTNodeStack_peek(root_stack), if_scope);
                            ASTNode *top = ASTNodeStack_pop(root_stack);
                            add_child(ASTNodeStack_peek(root_stack), top);
                        }
                        *token--;
                    }
                    *token--;
                }
                else if (strcmp(parent_node->value, "Else_Body") == 0)
                {
                    ASTNode *else_scope = ASTNodeStack_pop(root_stack);
                    ASTNode *if_body = ASTNodeStack_pop(root_stack);
                    ASTNode *if_scope = ASTNodeStack_pop(root_stack);
                    add_child(if_scope, if_body);
                    add_child(if_scope, else_scope);
                    add_child(ASTNodeStack_peek(root_stack), if_scope);
                }
                else if (strcmp(parent_node->value, "Function_Body") == 0 || strcmp(parent_node->value, "Loop_Body") == 0)
                {
                    ASTNode *body = ASTNodeStack_pop(root_stack);
                    ASTNode *scope = ASTNodeStack_pop(root_stack);
                    add_child(scope, body);
                    add_child(ASTNodeStack_peek(root_stack), scope);
                }
                else
                {
                    ASTNode *top = ASTNodeStack_pop(root_stack);
                    add_child(ASTNodeStack_peek(root_stack), top);
                }
            }
            // Invalid token occured
            else
            {
                fprintf(stderr, "Invalid token %s : %d (Value:Type) on line %d\n", token->value, token->type, line_count);
                exit(EXIT_FAILURE);
            }
        }
        *token++;
    }
    if (token->type != TOKEN_EOF)
    {
        fprintf(stderr, "Parser couldnt reach end of file\n");
        exit(EXIT_FAILURE);
    }
    add_child(root, create_ASTNode(NODE_EOF, "EOF"));
    return root;
}