#include "../include/utils/expression_eval.h"
#include "../include/parser.h"
#include "../include/memory.h"

// Function to check if a node is an operator
int is_node_operator(NodeType type)
{
    return type == NODE_ARITH_OP || type == NODE_LOGIC_OP || type == NODE_RELAT_OP;
}

// Function to get the precedence of an operator
int precedence(NodeType type, char *op)
{
    switch (type)
    {
    case NODE_ARITH_OP:
        if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0)
        {
            return 4;
        }
        return 3;
    case NODE_RELAT_OP:
        return 2;
    case NODE_LOGIC_OP:
        return 1;
    default:
        return -1;
    }
}

ASTNode *infix_to_postfix(ASTNode **expression, size_t size, ScopeStack *memory)
{
    ASTNode *output[size];
    size_t output_idx = 0;

    ASTNode *stack[size];
    size_t stack_idx = 0;

    for (size_t i = 0; i < size; ++i)
    {
        ASTNode *current = expression[i];

        if (current->type == NODE_O_PAREN)
        {
            stack[stack_idx++] = current;
        }
        else if (current->type == NODE_C_PAREN)
        {
            while (stack_idx > 0 && stack[stack_idx - 1]->type != NODE_O_PAREN)
            {
                output[output_idx++] = stack[--stack_idx];
            }
            if (stack_idx > 0 && stack[stack_idx - 1]->type == NODE_O_PAREN)
            {
                --stack_idx;
            }
        }
        else if (is_node_operator(current->type))
        {
            while (stack_idx > 0 && is_node_operator(stack[stack_idx - 1]->type) &&
                   precedence(stack[stack_idx - 1]->type, stack[stack_idx - 1]->value) >= precedence(current->type, current->value))
            {
                output[output_idx++] = stack[--stack_idx];
            }
            stack[stack_idx++] = current;
        }
        else if (current->type == NODE_ID)
        {
            output[output_idx++] = find_variable(memory, current->value)->value;
        }
        else
        {
            output[output_idx++] = current;
        }
    }

    while (stack_idx > 0)
    {
        output[output_idx++] = stack[--stack_idx];
    }

    ASTNode *res = create_ASTNode(NODE_EXPRESSION, "Postfix_Expression");
    for (size_t i = 0; i < output_idx; i++)
    {
        add_child(res, output[i]);
    }
    return res;
}

char *int_to_string(int number)
{
    int length = snprintf(NULL, 0, "%d", number);
    char *str = (char *)malloc((length + 1) * sizeof(char));

    if (str != NULL)
    {
        snprintf(str, length + 1, "%d", number);
    }
    return str;
}