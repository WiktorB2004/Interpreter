#include <string.h>
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/memory.h"
#include "../include/utils/expression_eval.h"
#include "../include/utils/ASTNode_Stack.h"

ASTNode *evaluate_expression(ASTNode *expression)
{
    // FIXME: Correcly hanlde operations on different types
    ASTNodeStack *stack = create_ASTNodeStack();
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
                int sum = atoi(val1->value) + atoi(val2->value);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(sum)));
            }
            else if (strcmp(curr->value, "-") == 0)
            {
                int diff = atoi(val2->value) - atoi(val1->value);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(diff)));
            }
            else if (strcmp(curr->value, "*") == 0)
            {
                int prod = atoi(val1->value) * atoi(val2->value);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(prod)));
            }
            else if (strcmp(curr->value, "/") == 0)
            {
                int quo = atoi(val2->value) / atoi(val1->value);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(quo)));
            }
            break;
        case NODE_LOGIC_OP:
            val1 = ASTNodeStack_pop(stack);
            val2 = ASTNodeStack_pop(stack);
            if (strcmp(curr->value, "||") == 0)
            {
                int sum = atoi(val1->value) == 1 || atoi(val2->value) == 1;
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(sum)));
            }
            else if (strcmp(curr->value, "&&") == 0)
            {
                int diff = atoi(val1->value) == 1 && atoi(val2->value) == 1;
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(diff)));
            }
            break;
        case NODE_RELAT_OP:
            val1 = ASTNodeStack_pop(stack);
            val2 = ASTNodeStack_pop(stack);
            if (strcmp(curr->value, "==") == 0)
            {
                int sum = atoi(val1->value) == atoi(val2->value);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(sum)));
            }
            else if (strcmp(curr->value, "!=") == 0)
            {
                int diff = atoi(val1->value) != atoi(val2->value);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(diff)));
            }
            else if (strcmp(curr->value, ">") == 0)
            {
                int diff = atoi(val2->value) > atoi(val1->value);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(diff)));
            }
            else if (strcmp(curr->value, ">=") == 0)
            {
                int prod = atoi(val2->value) >= atoi(val1->value);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(prod)));
            }
            else if (strcmp(curr->value, "<") == 0)
            {
                int quo = atoi(val2->value) < atoi(val1->value);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(quo)));
            }
            else if (strcmp(curr->value, "<=") == 0)
            {
                int quo = atoi(val2->value) <= atoi(val1->value);
                ASTNodeStack_push(stack, create_ASTNode(NODE_VAL, int_to_string(quo)));
            }
            break;
        default:
            break;
        }
    }
    return ASTNodeStack_peek(stack);
}

ASTNode *evaluate(ASTNode *node, ScopeStack *memory)
{
    if (node == NULL)
    {
        return NULL;
    }

    ASTNode *type, *name, *value, *value2, *params;
    switch (node->type)
    {
    // SECTION: Variables
    case NODE_V_DEF:;
        type = evaluate(node->children[0], memory);
        name = evaluate(node->children[1], memory);
        value = evaluate(node->children[2], memory);
        // FIXME: Validate values and create new variable
        add_variable(memory, type->value, name->value, value, NULL);
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
        ASTNode *postfix_epxression = infix_to_postfix(node->children, node->children_num, memory);
        return evaluate_expression(postfix_epxression);
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
            add_variable(memory, type->value, name->value, value, params);
        }
        else if (strcmp(node->value, "While_Loop") == 0)
        {
            push_scope(memory, 250);
            params = evaluate(node->children[0], memory);
            value = node->children[1];
            while (atoi(params->value) == 1)
            {
                evaluate(value, memory);
                params = evaluate(node->children[0], memory);
            }
            pop_scope(memory);
        }
        else if (strcmp(node->value, "Conditional_Scope") == 0)
        {
            params = evaluate(node->children[0], memory);
            value = node->children[1];
            if (atoi(params->value) == 1)
            {
                evaluate(value, memory);
            }
            else if (node->children[2] != NULL)
            {
                value2 = node->children[2];
                evaluate(value2, memory);
            }
        }
        else
        {
            if (strcmp(node->value, "User_Scope") == 0)
            {
                push_scope(memory, 500);
            }
            for (size_t i = 0; i < node->children_num; i++)
            {
                evaluate(node->children[i], memory);
            }
            if (strcmp(node->value, "User_Scope") == 0)
            {
                pop_scope(memory);
            }
        }
        break;
    // SECTION: Keywords
    case NODE_KEYWORD:
        if (strcmp(node->value, "Print") == 0)
        {
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
        Variable *param, *var, *function = find_variable(memory, name->value);
        ASTNode *curr;
        push_scope(memory, 250);
        for (size_t i = 0; i < params->children_num; i++)
        {
            curr = params->children[i];
            if (curr->type != NODE_ID)
            {
                add_variable(memory, "int", function->params->children[i]->value, curr, NULL);
            }
            else
            {
                var = find_variable(memory, curr->value);
                add_variable(memory, var->type, function->params->children[i]->value, var->value, NULL);
            }
        }
        evaluate(function->value, memory);
        pop_scope(memory);
        break;
    case NODE_RETURN:
        return evaluate(node->children[0], memory);
        break;
    default:
        for (size_t i = 0; i < node->children_num; i++)
        {
            evaluate(node->children[i], memory);
        }
        break;
    }
}