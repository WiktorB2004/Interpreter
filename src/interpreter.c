#include <string.h>
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/memory.h"
#include "../include/utils/expression_eval.h"

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
    case NODE_LIST_B:
        return node;
    case NODE_EXPRESSION:;
        ASTNode *postfix_epxression = infix_to_postfix(node->children, node->children_num, memory);
        value = evaluate_expression(postfix_epxression);
        if (value->type == NODE_VAL)
        {
            return value;
        }
        else
        {
            printf("Expression evaluation error: %s\n", value->value);
            exit(EXIT_FAILURE);
        }
        break;
    // SECTION: Functions
    case NODE_SCOPE:
        if (strcmp(node->value, "Function_Scope") == 0)
        {
            name = evaluate(node->children[0], memory);
            type = node->children[1];
            params = node->children[2];
            value = node->children[3];
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
            if (value->type == NODE_ID)
            {
                value = find_variable(memory, value->value)->value;
            }
            ASTNode *result;
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
            case NODE_EXPRESSION:;
                result = evaluate(value, memory);
                printf("%s\n", result->value);
                break;
            case NODE_FUNC_CALL:
                result = evaluate(value, memory);
                value2 = value->children[0];
                var = find_variable(memory, value2->value);
                printf("%s\n", var->return_value->value);
                break;
            case LIST_B:
                for (size_t i = 0; i < value->children_num; i++)
                {
                    printf("%s ", value->children[i]->value);
                }
                printf("\n");
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
                // FIXME: Get correct variable type
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
        return function->return_value;
        break;
    case NODE_RETURN:
        // FIXME: Validate return type and value
        // Return node
        value = node->children[0];
        // Returning function
        value2 = node->children[1];
        var = find_variable(memory, value2->value);
        if (value->type == NODE_EXPRESSION)
        {
            ASTNode *exp = infix_to_postfix(value->children, value->children_num, memory);
            var->return_value = evaluate_expression(exp);
        }
        else
        {
            if (value->type == NODE_ID)
            {
                Variable *var2 = find_variable(memory, value->value);
                var->return_value = var2->value;
            }
            else
            {
                var->return_value = value;
            }
        }
        break;
    default:
        for (size_t i = 0; i < node->children_num; i++)
        {
            evaluate(node->children[i], memory);
        }
        break;
    }
}