#include "unity.h"
#include "../include/utils_test.h"
#include "../include/parser.h"
#include "../include/utils/expression_eval.h"

ASTNode *input, *output;

void expression_edge_cases(void)
{
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    output = evaluate_expression(input);
    TEST_ASSERT_EQUAL_INT(NODE_ERROR, output->type);
    TEST_ASSERT_EQUAL_STRING("Empty expression", output->value);
    TEST_MESSAGE("Empty expression -> ok");

    free(input);
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    add_child(input, create_ASTNode(NODE_VAL, "1000000000000000"));
    add_child(input, create_ASTNode(NODE_VAL, "1"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "+"));

    output = evaluate_expression(input);
    printf("\n%s\n", output->value);
    TEST_ASSERT_EQUAL_INT(NODE_ERROR, output->type);
    TEST_ASSERT_EQUAL_STRING("Value out of storage limit", output->value);
    TEST_MESSAGE("Highest positive int value -> ok");

    free(input);
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    add_child(input, create_ASTNode(NODE_VAL, "-1000000000000000"));
    add_child(input, create_ASTNode(NODE_VAL, "1"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "-"));

    output = evaluate_expression(input);
    TEST_ASSERT_EQUAL_INT(NODE_ERROR, output->type);
    TEST_ASSERT_EQUAL_STRING("Value out of storage limit", output->value);
    TEST_MESSAGE("Lowest positive int value -> ok");
    free(input);
}

void int_expression_eval(void)
{
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    add_child(input, create_ASTNode(NODE_VAL, "2"));
    add_child(input, create_ASTNode(NODE_VAL, "1"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "+"));
    add_child(input, create_ASTNode(NODE_VAL, "6"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "*"));

    output = evaluate_expression(input);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, output->type);
    TEST_ASSERT_EQUAL_STRING("18", output->value);
    TEST_MESSAGE("(2 + 1) * 6 -> ok");

    free(input);
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    add_child(input, create_ASTNode(NODE_VAL, "-2"));
    add_child(input, create_ASTNode(NODE_VAL, "-1"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "*"));
    add_child(input, create_ASTNode(NODE_VAL, "3"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "*"));

    output = evaluate_expression(input);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, output->type);
    TEST_ASSERT_EQUAL_STRING("6", output->value);
    TEST_MESSAGE("-2 * -1 * 3 -> ok");

    free(input);
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    add_child(input, create_ASTNode(NODE_VAL, "-2"));
    add_child(input, create_ASTNode(NODE_VAL, "-1"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "*"));
    add_child(input, create_ASTNode(NODE_VAL, "-3"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "*"));
    output = evaluate_expression(input);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, output->type);
    TEST_ASSERT_EQUAL_STRING("-6", output->value);
    TEST_MESSAGE("-2 * -1 * -3 -> ok");

    free(input);
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    add_child(input, create_ASTNode(NODE_VAL, "-2"));
    add_child(input, create_ASTNode(NODE_VAL, "-1"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "-"));
    add_child(input, create_ASTNode(NODE_VAL, "-1"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "/"));
    output = evaluate_expression(input);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, output->type);
    TEST_ASSERT_EQUAL_STRING("1", output->value);
    TEST_MESSAGE("(-2 - (-1)) / -1 -> ok");

    free(input);
}

void float_expression_eval(void)
{
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    add_child(input, create_ASTNode(NODE_VAL, "2.1"));
    add_child(input, create_ASTNode(NODE_VAL, "1.2"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "+"));

    output = evaluate_expression(input);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, output->type);
    TEST_ASSERT_EQUAL_STRING("3.3", output->value);
    TEST_MESSAGE("2.1 + 1.2 -> ok");

    free(input);
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    add_child(input, create_ASTNode(NODE_VAL, "-2.1"));
    add_child(input, create_ASTNode(NODE_VAL, "-1.2"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "-"));

    output = evaluate_expression(input);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, output->type);
    TEST_ASSERT_EQUAL_STRING("-0.9", output->value);
    TEST_MESSAGE("-2.1 - -1.2 -> ok");

    free(input);
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    add_child(input, create_ASTNode(NODE_VAL, "50"));
    add_child(input, create_ASTNode(NODE_VAL, "0.5"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "*"));
    output = evaluate_expression(input);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, output->type);
    TEST_ASSERT_EQUAL_STRING("25", output->value);
    TEST_MESSAGE("50 * 0.5 -> ok");

    free(input);
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    add_child(input, create_ASTNode(NODE_VAL, "50"));
    add_child(input, create_ASTNode(NODE_VAL, "0.5"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "/"));
    output = evaluate_expression(input);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, output->type);
    TEST_ASSERT_EQUAL_STRING("100", output->value);
    TEST_MESSAGE("50 / 0.5 -> ok");

    free(input);
    input = create_ASTNode(NODE_EXPRESSION, "Expression");
    add_child(input, create_ASTNode(NODE_VAL, "55.2"));
    add_child(input, create_ASTNode(NODE_VAL, "2"));
    add_child(input, create_ASTNode(NODE_ARITH_OP, "/"));
    output = evaluate_expression(input);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, output->type);
    TEST_ASSERT_EQUAL_STRING("27.6", output->value);
    TEST_MESSAGE("55.5 / 2 -> ok");

    free(input);
}