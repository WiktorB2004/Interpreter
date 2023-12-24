#include "unity.h"
#include "../../include/lexer.h"
#include "../../include/parser.h"
#include "../include/parser_test.h"

// FIXME: If possible when using good practices - include each input -> output in setUp function instead making this in each test

static ASTNode *output, *test_node;
static Token *tokens;
static char *input;
static int num_tokens;

void function_scope(void)
{
    input = "DEF func -> int () {\nint num1 = 1;\nstring str = \"str\";\nPRINT str;\nreturn num1;\n}";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Function Scope test
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);

    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_R_TYPE, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_PARAMETERS, test_node->children[2]->type);
    TEST_ASSERT_EQUAL_STRING("Function_Scope", test_node->value);
    TEST_ASSERT_EQUAL_STRING("func", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("int", test_node->children[1]->value);
    // Function body test
    test_node = output->children[0]->children[3];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Function_Body", test_node->value);

    TEST_ASSERT_EQUAL_INT(NODE_V_DEF, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_V_DEF, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_KEYWORD, test_node->children[2]->type);
    TEST_ASSERT_EQUAL_INT(NODE_RETURN, test_node->children[3]->type);

    TEST_MESSAGE("Single function scope-> ok");
    input = "DEF func -> int () {\nDEF func2 -> void () {\n PRINT \"HELLO\"; \n} return 1;\n}";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Function Scope test
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);

    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_R_TYPE, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_STRING("Function_Scope", test_node->value);
    TEST_ASSERT_EQUAL_STRING("func", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("int", test_node->children[1]->value);
    // Function body test
    test_node = output->children[0]->children[3];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Function_Body", test_node->value);

    TEST_ASSERT_EQUAL_INT(NODE_RETURN, test_node->children[1]->type);
    // Nested function scope test
    test_node = output->children[0]->children[3]->children[0];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Function_Scope", test_node->value);

    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_R_TYPE, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_PARAMETERS, test_node->children[2]->type);
    // Nested function body test
    test_node = output->children[0]->children[3]->children[0]->children[3];
    TEST_ASSERT_EQUAL_INT(NODE_KEYWORD, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_STRING("Print", test_node->children[0]->value);

    TEST_MESSAGE("Nested function scope -> ok");
}

void user_scope(void)
{
    input = "DEF func -> int () {\n{int num1 = 1;\nstring str = \"str\";}\nreturn num1;\n}";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Function body test
    test_node = output->children[0]->children[3];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Function_Body", test_node->value);

    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_RETURN, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_STRING("User_Scope", test_node->children[0]->value);
    // User scope test
    test_node = output->children[0]->children[3]->children[0];
    TEST_ASSERT_EQUAL_INT(NODE_V_DEF, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_V_DEF, test_node->children[1]->type);

    TEST_MESSAGE("Single function scope-> ok");
    input = "DEF func -> int () {\n{int num1 = 1;\n{string str = \"str\";}\n}\nreturn num1;\n}";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Function body test
    test_node = output->children[0]->children[3];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Function_Body", test_node->value);

    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_RETURN, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_STRING("User_Scope", test_node->children[0]->value);
    // User scope test
    test_node = output->children[0]->children[3]->children[0];
    TEST_ASSERT_EQUAL_INT(NODE_V_DEF, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_STRING("User_Scope", test_node->children[1]->value);
    // Nested user scope test
    test_node = output->children[0]->children[3]->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_V_DEF, test_node->children[0]->type);

    TEST_MESSAGE("Nested user scope -> ok");
}

void if_scope(void)
{
    input = "IF (num1 > 1) {\nPRINT \"Hello\";\n} ELSE {\nPRINT \"World\";}";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Conditional Scope test
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Conditional_Scope", test_node->value);
    // Conditions
    test_node = output->children[0]->children[0];
    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->type);
    // If Body
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("If_Body", test_node->value);
    // Else Body
    test_node = output->children[0]->children[2];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Else_Body", test_node->value);

    TEST_MESSAGE("Single if statement -> ok");
    input = "IF (1 > 1) {\nIF (1 == 0) {\nPRINT \" World\";\n} ELSE {\nPRINT \"1\";\n}\n} ELSE {\nIF (1 == 1) {\nPRINT \" 2 \";\n} ELSE {\nPRINT \"3\";\n}\n}";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Conditional Scope test
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Conditional_Scope", test_node->value);
    // Conditions
    test_node = output->children[0]->children[0];
    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->type);
    // If Body
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("If_Body", test_node->value);
    // 1. Nested Conditional Scope
    test_node = output->children[0]->children[1]->children[0];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Conditional_Scope", test_node->value);
    // 1. Nested If Body
    test_node = output->children[0]->children[1]->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("If_Body", test_node->value);
    // 1. Nested Else Body
    test_node = output->children[0]->children[1]->children[0]->children[2];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Else_Body", test_node->value);
    // Else Body
    test_node = output->children[0]->children[2];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Else_Body", test_node->value);
    // 2. Nested Conditional Scope
    test_node = output->children[0]->children[2]->children[0];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Conditional_Scope", test_node->value);
    // 2. Nested If Body
    test_node = output->children[0]->children[2]->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("If_Body", test_node->value);
    // 2. Nested Else Body
    test_node = output->children[0]->children[2]->children[0]->children[2];
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_STRING("Else_Body", test_node->value);

    TEST_MESSAGE("Nested if/else -> ok");
}

void while_scope(void)
{
    input = "WHILE (cond == 1) {\n PRINT \"Hello\";}";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    TEST_MESSAGE("Single while loop -> ok");
    input = "WHILE (cond == 1) {\n WHILE (cond2 == 1) {\n PRINT \"World\";}}";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    TEST_MESSAGE("Nested While loop -> ok");
}