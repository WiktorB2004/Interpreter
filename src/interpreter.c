#include <string.h>
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/utils/ASTNode_Stack.h"

void init_SymbolTable(SymbolTable *sym_table)
{
    sym_table->count = 0;
}

void print_SymbolTable(SymbolTable *table)
{
    printf("========== Symbol Table ==========\n");
    for (int i = 0; i < table->count; i++)
    {
        printf("%s %s\n", table->variables[i].name, table->variables[i].type);
        print_ASTree(table->variables[i].params, 0);
        print_ASTree(table->variables[i].value, 0);
    }
    printf("=================================\n");
}

void enter_scope(SymbolTable **memory_stack, int current_scope)
{
    if (current_scope < 499)
    {
        memory_stack[++current_scope] = (SymbolTable *)malloc(sizeof(SymbolTable));
        memory_stack[current_scope]->count = 0;
    }
    else
    {
        printf("Maximum scope depth reached!\n");
    }
}

Variable *create_variable(char *type, char *name, ASTNode *value, ASTNode *params)
{
    Variable *new_variable = (Variable *)malloc(sizeof(Variable));
    if (new_variable == NULL)
    {
        fprintf(stderr, "Memory allocation failed for creating ASTNode.\n");
        exit(EXIT_FAILURE);
    }
    if (value != NULL && type != NULL && name != NULL)
    {
        new_variable->type = strdup(type);
        new_variable->name = strdup(name);
        new_variable->value = value;
        new_variable->params = params;
    }
    return new_variable;
}

void insert_variable(SymbolTable *table, Variable *var)
{
    if (table->count < 5000)
    {
        table->variables[table->count++] = *var;
    }
    else
    {
        printf("Variable table is full!\n");
    }
}

void modify_variable_value(SymbolTable *table, char *name, ASTNode *value_node)
{
    for (int i = 0; i < table->count; i++)
    {
        if (strcmp(table->variables[i].name, name) == 0)
        {
            table->variables[i].value = value_node;
            return;
        }
    }
    fprintf(stderr, "Changing value of nonexistent variable.\n");
    exit(EXIT_FAILURE);
}

Variable *find_variable(SymbolTable *table, char *name)
{
    for (int i = 0; i < table->count; i++)
    {
        if (strcmp(table->variables[i].name, name) == 0)
        {
            return &table->variables[i];
        }
    }
    fprintf(stderr, "Value is not in memory.\n");
    exit(EXIT_FAILURE);
}

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

ASTNode *infix_to_postfix(ASTNode **expression, size_t size, SymbolTable *memory)
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

ASTNode *evaluate(ASTNode *node, SymbolTable *memory)
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
        insert_variable(memory, create_variable(type->value, name->value, value, NULL));
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
            insert_variable(memory, create_variable(type->value, name->value, value, params));
        }
        else if (strcmp(node->value, "While_Loop") == 0)
        {
            params = evaluate(node->children[0], memory);
            value = node->children[1];
            while (atoi(params->value) == 1)
            {
                evaluate(value, memory);
                params = evaluate(node->children[0], memory);
            }
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
            for (size_t i = 0; i < node->children_num; i++)
            {
                evaluate(node->children[i], memory);
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
        for (size_t i = 0; i < params->children_num; i++)
        {
            curr = params->children[i];
            if (curr->type != NODE_ID)
            {
                param = create_variable("int", function->params->children[i]->value, curr, NULL);
                insert_variable(memory, param);
            }
            else
            {
                var = find_variable(memory, curr->value);
                param = create_variable(var->type, function->params->children[i]->value, var->value, NULL);
                insert_variable(memory, param);
            }
        }
        evaluate(function->value, memory);
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