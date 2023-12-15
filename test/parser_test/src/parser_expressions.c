#include "unity.h"
#include "../../include/lexer.h"
#include "../../include/parser.h"
#include "../include/parser_test.h"

// FIXME: If possible when using good practices - include each input -> output in setUp function instead making this in each test

ASTNode *output, *test_node;
Token *tokens;
char *input;
int num_tokens;

void arithmetic_expression(void)
{
    input = "test = (1 + num1) * 2 / a - 5;";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];
    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(11, test_node->children[1]->children_num);
    // Expression types
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_O_PAREN, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ARITH_OP, test_node->children[2]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[3]->type);
    TEST_ASSERT_EQUAL_INT(NODE_C_PAREN, test_node->children[4]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ARITH_OP, test_node->children[5]->type);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[6]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ARITH_OP, test_node->children[7]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[8]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ARITH_OP, test_node->children[9]->type);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[10]->type);
    // Expression values
    TEST_ASSERT_EQUAL_STRING("(", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("1", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("+", test_node->children[2]->value);
    TEST_ASSERT_EQUAL_STRING("num1", test_node->children[3]->value);
    TEST_ASSERT_EQUAL_STRING(")", test_node->children[4]->value);
    TEST_ASSERT_EQUAL_STRING("*", test_node->children[5]->value);
    TEST_ASSERT_EQUAL_STRING("2", test_node->children[6]->value);
    TEST_ASSERT_EQUAL_STRING("/", test_node->children[7]->value);
    TEST_ASSERT_EQUAL_STRING("a", test_node->children[8]->value);
    TEST_ASSERT_EQUAL_STRING("-", test_node->children[9]->value);
    TEST_ASSERT_EQUAL_STRING("5", test_node->children[10]->value);

    TEST_MESSAGE("(1 + 2) * 2 / 2 - 5 -> ok");
}

void logic_expression(void)
{
    input = "test = 1 && a;";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(3, test_node->children[1]->children_num);
    // Expression types
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_LOGIC_OP, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[2]->type);
    // Expression values
    TEST_ASSERT_EQUAL_STRING("1", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("&&", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("a", test_node->children[2]->value);

    TEST_MESSAGE("1 && a -> ok");
    input = "test = 1 || a;";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(3, test_node->children[1]->children_num);
    // Expression types
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_LOGIC_OP, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[2]->type);
    // Expression values
    TEST_ASSERT_EQUAL_STRING("1", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("||", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("a", test_node->children[2]->value);

    TEST_MESSAGE("1 || a -> ok");
}

void relational_expression(void)
{
    input = "test = num1 == 2;";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(3, test_node->children[1]->children_num);
    // Expression types
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_RELAT_OP, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[2]->type);
    // Expression values
    TEST_ASSERT_EQUAL_STRING("num1", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("==", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("2", test_node->children[2]->value);

    TEST_MESSAGE("num1 == 2 -> ok");
    input = "test = 1 != hello_world;";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(3, test_node->children[1]->children_num);
    // Expression types
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_RELAT_OP, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[2]->type);
    // Expression values
    TEST_ASSERT_EQUAL_STRING("1", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("!=", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("hello_world", test_node->children[2]->value);

    TEST_MESSAGE("1 != hello_world;");
    input = "test = 1 >= num1;";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(3, test_node->children[1]->children_num);
    // Expression types
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_RELAT_OP, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[2]->type);
    // Expression values
    TEST_ASSERT_EQUAL_STRING("1", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING(">=", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("num1", test_node->children[2]->value);

    TEST_MESSAGE("1 >= num1 -> ok");
    input = "test = 1 > a;";
    Token *tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(3, test_node->children[1]->children_num);
    // Expression types
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_RELAT_OP, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[2]->type);
    // Expression values
    TEST_ASSERT_EQUAL_STRING("1", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING(">", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("a", test_node->children[2]->value);

    TEST_MESSAGE("1 > a -> ok");
    input = "test = 1 <= a;";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(3, test_node->children[1]->children_num);
    // Expression types
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_RELAT_OP, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[2]->type);
    // Expression values
    TEST_ASSERT_EQUAL_STRING("1", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("<=", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("a", test_node->children[2]->value);

    TEST_MESSAGE("1 <= a -> ok");
    input = "test = 1 < a;";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(3, test_node->children[1]->children_num);
    // Expression types
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_RELAT_OP, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[2]->type);
    // Expression values
    TEST_ASSERT_EQUAL_STRING("1", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("<", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("a", test_node->children[2]->value);
    ;

    TEST_MESSAGE("1 < a -> ok");
}

void mixed_expression(void)
{
    input = "test = (1 + 2) * 2 / 2;";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // TEST_ASSERT_EQUAL_INT(NODE_V_TYPE, test_node->children[0]->type);
    // TEST_ASSERT_EQUAL_STRING("int", test_node->children[0]->value);

    TEST_MESSAGE("(1 + 2) * 2 / 2 -> ok");
}