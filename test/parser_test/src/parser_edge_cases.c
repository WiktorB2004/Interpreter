#include "unity.h"
#include "../../include/lexer.h"
#include "../../include/parser.h"
#include "../include/parser_test.h"

// FIXME: If possible when using good practices - include each input -> output in setUp function instead making this in each test

ASTNode *output, *test_node;
char *input;
int num_tokens;

// Empty input test case
void empty_input(void)
{
    input = "";
    Token *tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);

    TEST_ASSERT_EQUAL_INT(1, output[0].children_num);
    TEST_ASSERT_EQUAL_INT(NODE_ROOT, output[0].type);

    TEST_ASSERT_EQUAL_INT(NODE_EOF, output[0].children[0]->type);
}

// FIXME: Create error handler and then implement syntax erorrs handler
void syntax_errors(void)
{
    input = "";
    Token *tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);

    TEST_MESSAGE("Syntax error name -> ok");
}
