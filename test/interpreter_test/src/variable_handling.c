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

void variable_declaration(void)
{
    input = "int num = 0;";
    tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    init_ScopeStack(&memory, 10);
    push_scope(&memory, 10);
    evaluate(tree, &memory);
    test_node = find_variable(&memory, "num")->value;
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("0", test_node->value);
    TEST_MESSAGE("Int declaration -> ok");

    input = "string str = \"Hello World\";";
    tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    init_ScopeStack(&memory, 10);
    push_scope(&memory, 10);

    evaluate(tree, &memory);
    test_node = find_variable(&memory, "str")->value;
    TEST_ASSERT_EQUAL_INT(NODE_T_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("\"Hello World\"", test_node->value);
    TEST_MESSAGE("String declaration -> ok");

    input = "char chr = '0';";
    tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    init_ScopeStack(&memory, 10);
    push_scope(&memory, 10);
    evaluate(tree, &memory);
    test_node = find_variable(&memory, "chr")->value;
    TEST_ASSERT_EQUAL_INT(NODE_T_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("'0'", test_node->value);
    TEST_MESSAGE("Char declaration -> ok");
}

void variable_modification(void)
{
    input = "int num = 0;\nnum = 1;";
    tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    init_ScopeStack(&memory, 10);
    push_scope(&memory, 10);
    evaluate(tree, &memory);
    test_node = find_variable(&memory, "num")->value;
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("1", test_node->value);
    TEST_MESSAGE("Int modification -> ok");
    input = "string str = \"Hello World\";\nstr = \"Bye World\";";
    tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    init_ScopeStack(&memory, 10);
    push_scope(&memory, 10);

    evaluate(tree, &memory);
    test_node = find_variable(&memory, "str")->value;
    TEST_ASSERT_EQUAL_INT(NODE_T_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("\"Bye World\"", test_node->value);
    TEST_MESSAGE("String modification -> ok");

    input = "char chr = '0';\nchr = 'c';";
    tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    init_ScopeStack(&memory, 10);
    push_scope(&memory, 10);
    evaluate(tree, &memory);
    test_node = find_variable(&memory, "chr")->value;
    TEST_ASSERT_EQUAL_INT(NODE_T_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("'c'", test_node->value);
    TEST_MESSAGE("Char modification -> ok");
}

void variable_scoping(void)
{
    input = "int num1 = 0;\nint num2 = 0;\nint num3 = 3;\nDEF main -> void () {\nnum1 = 1; \n{\nnum2 = 2;\nint num3 = 1;\nint num4 = -1;\n}\nint num5 = 1;\n}\nmain();";
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
    test_node = find_variable(&memory, "num3")->value;
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("3", test_node->value);
    var = find_variable(&memory, "num4");
    TEST_ASSERT_NULL(var);
    var = find_variable(&memory, "num5");
    TEST_ASSERT_NULL(var);
}

void variable_accessing(void)
{
    input = "int num1 = 0;\nchar ch = 'c';\nstring str = \"Hello World\";";
    tokens = lexer(input, &num_tokens);
    tree = parse_program(&tokens);
    init_ScopeStack(&memory, 10);
    push_scope(&memory, 10);
    output = evaluate(tree, &memory);
    test_node = find_variable(&memory, "num1")->value;
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("0", test_node->value);
    test_node = find_variable(&memory, "ch")->value;
    TEST_ASSERT_EQUAL_INT(NODE_T_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("'c'", test_node->value);
    test_node = find_variable(&memory, "str")->value;
    TEST_ASSERT_EQUAL_INT(NODE_T_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("\"Hello World\"", test_node->value);
    var = find_variable(&memory, "num4");
    TEST_ASSERT_NULL(var);
}