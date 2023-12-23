#include <float.h>
#include "../include/utils/expression_eval.h"
#include "../include/utils/ASTNode_Stack.h"
#include "../include/parser.h"
#include "../include/memory.h"

#define MAX_NUM 100000000000000
#define MIN_NUM -100000000000000

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

char *num_to_string(double number)
{
    char *str = NULL;
    int len;

    if (number == (int)number)
    {
        len = snprintf(NULL, 0, "%.0lf", number);
    }
    else
    {
        len = snprintf(NULL, 0, "%.15lg", number);
    }

    str = (char *)malloc((len + 1) * sizeof(char));

    if (str != NULL)
    {
        if (number == (int)number)
        {
            sprintf(str, "%.0lf", number);
        }
        else
        {
            sprintf(str, "%.15lg", number);
            char *end = str + len - 1;
            while (*end == '0')
            {
                *end-- = '\0';
            }
            if (*end == '.')
            {
                *end = '\0';
            }
        }
    }

    return str;
}

ASTNode *evaluate_expression(ASTNode *expression)
{
    ASTNodeStack *stack = create_ASTNodeStack();
    if (expression->children_num == 0)
    {
        return create_ASTNode(NODE_ERROR, "Empty expression");
    }
    for (size_t i = 0; i < expression->children_num; ++i)
    {
        ASTNode *curr = expression->children[i];
        ASTNode *val1, *val2;
        switch (curr->type)
        {
        case NODE_VAL:
        case NODE_T_VAL:
            ASTNodeStack_push(stack, curr);
            break;
        case NODE_ARITH_OP:
            val1 = ASTNodeStack_pop(stack);
            val2 = ASTNodeStack_pop(stack);
            if (strcmp(curr->value, "+") == 0)
            {
                double sum = atof(val1->value) + atof(val2->value);
                if (sum > MAX_NUM || sum < MIN_NUM)
                {
                    return create_ASTNode(NODE_ERROR, "Value out of storage limit");
                }
                else
                {
                    ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(sum)));
                }
            }
            else if (strcmp(curr->value, "-") == 0)
            {
                double diff = atof(val2->value) - atof(val1->value);
                if (diff > MAX_NUM || diff < MIN_NUM)
                {
                    return create_ASTNode(NODE_ERROR, "Value out of storage limit");
                }
                else
                {
                    ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(diff)));
                }
            }
            else if (strcmp(curr->value, "*") == 0)
            {
                double prod = atof(val1->value) * atof(val2->value);
                if (prod > MAX_NUM || prod < MIN_NUM)
                {
                    return create_ASTNode(NODE_ERROR, "Value out of storage limit");
                }
                else
                {
                    ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(prod)));
                }
            }
            else if (strcmp(curr->value, "/") == 0)
            {
                double quo = atof(val2->value) / atof(val1->value);
                if (quo > MAX_NUM || quo < MIN_NUM)
                {
                    return create_ASTNode(NODE_ERROR, "Value out of storage limit");
                }
                else
                {
                    ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(quo)));
                }
            }
            break;
        case NODE_LOGIC_OP:
            val1 = ASTNodeStack_pop(stack);
            val2 = ASTNodeStack_pop(stack);
            if (strcmp(curr->value, "||") == 0)
            {
                int res = atoi(val1->value) == 1 || atoi(val2->value) == 1;
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(res)));
            }
            else if (strcmp(curr->value, "&&") == 0)
            {
                int res = atoi(val1->value) == 1 && atoi(val2->value) == 1;
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(res)));
            }
            break;
        case NODE_RELAT_OP:
            val1 = ASTNodeStack_pop(stack);
            val2 = ASTNodeStack_pop(stack);
            char *endptr;
            if (strcmp(curr->value, "==") == 0)
            {
                int res = strtod(val1->value, &endptr) == strtod(val2->value, &endptr);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(res)));
            }
            else if (strcmp(curr->value, "!=") == 0)
            {
                int res = strtod(val1->value, &endptr) != strtod(val2->value, &endptr);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(res)));
            }
            else if (strcmp(curr->value, ">") == 0)
            {
                int res = strtod(val2->value, &endptr) > strtod(val1->value, &endptr);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(res)));
            }
            else if (strcmp(curr->value, ">=") == 0)
            {
                int res = strtod(val2->value, &endptr) >= strtod(val1->value, &endptr);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(res)));
            }
            else if (strcmp(curr->value, "<") == 0)
            {
                int res = strtod(val2->value, &endptr) < strtod(val1->value, &endptr);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(res)));
            }
            else if (strcmp(curr->value, "<=") == 0)
            {
                int res = strtod(val2->value, &endptr) <= strtod(val1->value, &endptr);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, num_to_string(res)));
            }
            break;
        default:
            break;
        }
    }
    return ASTNodeStack_peek(stack);
}