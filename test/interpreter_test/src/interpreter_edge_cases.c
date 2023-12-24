#include "unity.h"
#include "../../include/lexer.h"
#include "../../include/parser.h"
#include "../../include/interpreter.h"
#include "../../include/memory.h"
#include "../include/interpreter_test.h"

static ASTNode *output, *tree, *test_node;
static ScopeStack memory;
static char *input;
static int num_tokens;

void empty_input(void)
{
    init_ScopeStack(&memory, 50);
    push_scope(&memory, 200);
    input = "";
    Token *tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    output = evaluate(tree, &memory);
    TEST_ASSERT_NULL(output);
}