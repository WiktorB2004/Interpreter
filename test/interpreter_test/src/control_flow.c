#include "unity.h"
#include "../../include/lexer.h"
#include "../../include/parser.h"
#include "../../include/interpreter.h"
#include "../../include/memory.h"
#include "../include/interpreter_test.h"

Token *tokens;
ASTNode *output, *tree, *test_node;
static ScopeStack memory;
Variable *var;
char *input;
static int num_tokens;

void if_statement(void)
{
    input = "int num1 = 0;\nint num2 = 0;\nIF (num1 == 0) {\nnum1 = 1;} ELSE {\nnum1 = 2;\n}\nIF (num1 != 1) {\nnum2 = 0;} ELSE {\nnum2 = 2;\n}";
    tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    init_ScopeStack(&memory, 10);
    push_scope(&memory, 10);
    evaluate(tree, &memory);
    test_node = find_variable(&memory, "num1")->value;
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("1", test_node->value);
    test_node = find_variable(&memory, "num2")->value;
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("2", test_node->value);
}

void while_loop(void)
{
    input = "int num1 = 0;\nint num2 = 5;\nWHILE (num1 < 5) {\nnum2 = num2 - 1;\nnum1 = num1 + 1;\n}";
    tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    init_ScopeStack(&memory, 10);
    push_scope(&memory, 10);
    evaluate(tree, &memory);
    test_node = find_variable(&memory, "num1")->value;
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("5", test_node->value);
    test_node = find_variable(&memory, "num2")->value;
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("0", test_node->value);
}

void function_call(void)
{
    input = "int num2 = 0;\nDEF main -> void (a, b) {\nnum2 = 3;\nreturn a + b;\n}\nint num1 = main(1, 3);";
    tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    init_ScopeStack(&memory, 10);
    push_scope(&memory, 10);
    evaluate(tree, &memory);
    test_node = find_variable(&memory, "num1")->value;
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("4", test_node->value);
    test_node = find_variable(&memory, "num2")->value;
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("3", test_node->value);
    input = "int num1 = 0;\nDEF main -> void () {\nnum1 = 1;\n}\nmain();";
    tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    init_ScopeStack(&memory, 10);
    push_scope(&memory, 10);
    evaluate(tree, &memory);
    test_node = find_variable(&memory, "num1")->value;
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("1", test_node->value);
}