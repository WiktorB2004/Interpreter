#include "unity.h"
#include "../../include/lexer.h"
#include "../../include/parser.h"
#include "../../include/interpreter.h"
#include "../../include/memory.h"
#include "../include/interpreter_test.h"

ASTNode *output, *tree, *test_node;
char *input;
int num_tokens;

void empty_input(void)
{
    ScopeStack memory;
    init_ScopeStack(&memory, 50);
    push_scope(&memory, 200);
    input = "";
    Token *tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    output = evaluate(tree, &memory);
    TEST_ASSERT_NULL(output);
}