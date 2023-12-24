#include "unity.h"
#include "../../include/lexer.h"
#include "../../include/parser.h"
#include "../include/parser_test.h"

// FIXME: If possible when using good practices - include each input -> output in setUp function instead making this in each test

ASTNode *output, *test_node;
char *input;
static int num_tokens;

void variable_declaration(void)
{
    input = "int num1 = 123;";
    Token *tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_V_TYPE, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[2]->type);

    // Node values
    TEST_ASSERT_EQUAL_STRING("int", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("num1", test_node->children[1]->value);
    // Expression
    test_node = test_node->children[2];
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_STRING("123", test_node->children[0]->value);

    TEST_MESSAGE("Int declaration -> ok");
    input = "string str = \"123\";";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_V_TYPE, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[2]->type);

    // Node values
    TEST_ASSERT_EQUAL_STRING("string", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("str", test_node->children[1]->value);
    // Expression
    test_node = test_node->children[2];
    TEST_ASSERT_EQUAL_INT(NODE_T_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_STRING("\"123\"", test_node->children[0]->value);

    TEST_MESSAGE("String declaration -> ok");
    input = "char c = \'c\';";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_V_TYPE, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[2]->type);

    // Node values
    TEST_ASSERT_EQUAL_STRING("char", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("c", test_node->children[1]->value);
    // Expression
    test_node = test_node->children[2];
    TEST_ASSERT_EQUAL_INT(NODE_T_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_STRING("\'c\'", test_node->children[0]->value);
    TEST_MESSAGE("Char declaration -> ok");
}

void variable_assignment(void)
{
    input = "num1 = -1.52;";
    Token *tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);

    // Node values
    TEST_ASSERT_EQUAL_STRING("num1", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("Expression", test_node->children[1]->value);
    // Expression
    test_node = test_node->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->type);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_STRING("-1.52", test_node->children[0]->value);

    TEST_MESSAGE("Int assignment -> ok");
    input = "str = \".25,!\";";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    // Node values
    TEST_ASSERT_EQUAL_STRING("str", test_node->children[0]->value);
    // Expression
    test_node = test_node->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_T_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("\".25,!\"", test_node->value);

    TEST_MESSAGE("String assignment -> ok");
    input = "chr = \'.\';";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    // Node values
    TEST_ASSERT_EQUAL_STRING("chr", test_node->children[0]->value);
    // Expression
    test_node = test_node->children[1];
    TEST_ASSERT_EQUAL_INT(NODE_T_VAL, test_node->type);
    TEST_ASSERT_EQUAL_STRING("\'.\'", test_node->value);
    TEST_MESSAGE("Char assignment -> ok");
}

void function_declaration(void)
{
    input = "DEF func -> int (a, b) {string str = \"Hello World\";}";
    Token *tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_R_TYPE, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_PARAMETERS, test_node->children[2]->type);
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->children[3]->type);

    // Node values
    TEST_ASSERT_EQUAL_STRING("Function_Scope", test_node->value);
    TEST_ASSERT_EQUAL_STRING("func", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("int", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("Parameters_List", test_node->children[2]->value);
    TEST_ASSERT_EQUAL_STRING("Function_Body", test_node->children[3]->value);
    // Parameters list
    test_node = output->children[0]->children[2];
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_STRING("a", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("b", test_node->children[1]->value);
    // Function Body
    test_node = output->children[0]->children[3];
    TEST_ASSERT_EQUAL_INT(1, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_V_DEF, test_node->children[0]->type);
}

void print_statement(void)
{
    input = "PRINT id;";
    Token *tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_KEYWORD, test_node->type);
    TEST_ASSERT_EQUAL_INT(1, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    // Node values
    TEST_ASSERT_EQUAL_STRING("id", test_node->children[0]->value);

    TEST_MESSAGE("Variable print -> ok");
    input = "PRINT hello_world(a, 5);";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Print Node types
    TEST_ASSERT_EQUAL_INT(NODE_KEYWORD, test_node->type);
    TEST_ASSERT_EQUAL_INT(1, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_FUNC_CALL, test_node->children[0]->type);
    // Function call Node Types
    test_node = output->children[0]->children[0];
    TEST_ASSERT_EQUAL_INT(NODE_FUNC_CALL, test_node->type);
    TEST_ASSERT_EQUAL_INT(2, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_PARAMETERS, test_node->children[1]->type);
    // Function call Node Values
    TEST_ASSERT_EQUAL_STRING("hello_world", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("Function_Parameters", test_node->children[1]->value);
    // Function Parameters
    test_node = test_node->children[1];
    TEST_ASSERT_EQUAL_INT(2, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[1]->type);
    // Function parameters value
    TEST_ASSERT_EQUAL_STRING("a", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("5", test_node->children[1]->value);

    TEST_MESSAGE("Function call print -> ok");
    input = "PRINT 5;";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[0]->type);
    // Node values
    TEST_ASSERT_EQUAL_STRING("5", test_node->children[0]->children[0]->value);

    TEST_MESSAGE("Value print -> ok");
    input = "PRINT \"Hello\";";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_T_VAL, test_node->children[0]->type);
    // Node values
    TEST_ASSERT_EQUAL_STRING("\"Hello\"", test_node->children[0]->value);

    TEST_MESSAGE("Text value print -> ok");
}

void conditional_statement(void)
{
    input = "IF (5 > id) {PRINT \"OK\";}";
    Token *tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_INT(2, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->children[1]->type);

    // Node values
    TEST_ASSERT_EQUAL_STRING("Conditional_Scope", test_node->value);
    TEST_ASSERT_EQUAL_STRING("Conditions", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("If_Body", test_node->children[1]->value);
    // Conditions
    test_node = output->children[0]->children[0];
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_RELAT_OP, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[2]->type);
    TEST_ASSERT_EQUAL_STRING("5", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING(">", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("id", test_node->children[2]->value);
    // If body
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(1, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_KEYWORD, test_node->children[0]->type);

    TEST_MESSAGE("IF statement -> ok");
    input = "IF (5 > id) {PRINT \"OK\";} ELSE {PRINT \"OK2\";}";
    tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Node types
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->type);
    TEST_ASSERT_EQUAL_INT(3, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_EXPRESSION, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_SCOPE, test_node->children[2]->type);

    // Node values
    TEST_ASSERT_EQUAL_STRING("Conditional_Scope", test_node->value);
    TEST_ASSERT_EQUAL_STRING("Conditions", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("If_Body", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("Else_Body", test_node->children[2]->value);
    // Conditions
    test_node = output->children[0]->children[0];
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_RELAT_OP, test_node->children[1]->type);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[2]->type);
    TEST_ASSERT_EQUAL_STRING("5", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING(">", test_node->children[1]->value);
    TEST_ASSERT_EQUAL_STRING("id", test_node->children[2]->value);
    // If body
    test_node = output->children[0]->children[1];
    TEST_ASSERT_EQUAL_INT(1, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_KEYWORD, test_node->children[0]->type);
    // Else body
    test_node = output->children[0]->children[2];
    TEST_ASSERT_EQUAL_INT(1, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_KEYWORD, test_node->children[0]->type);

    TEST_MESSAGE("IF/ELSE statement -> ok");
}

void function_call(void)
{
    input = "hello_world(a, 5);";
    Token *tokens = lexer(input, &num_tokens);
    output = parse_program(&tokens);
    test_node = output->children[0];

    // Function call Node Types
    TEST_ASSERT_EQUAL_INT(NODE_FUNC_CALL, test_node->type);
    TEST_ASSERT_EQUAL_INT(2, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_PARAMETERS, test_node->children[1]->type);
    // Function call Node Values
    TEST_ASSERT_EQUAL_STRING("hello_world", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("Function_Parameters", test_node->children[1]->value);
    // Function Parameters
    test_node = test_node->children[1];
    TEST_ASSERT_EQUAL_INT(2, test_node->children_num);
    TEST_ASSERT_EQUAL_INT(NODE_ID, test_node->children[0]->type);
    TEST_ASSERT_EQUAL_INT(NODE_VAL, test_node->children[1]->type);
    // Function parameters value
    TEST_ASSERT_EQUAL_STRING("a", test_node->children[0]->value);
    TEST_ASSERT_EQUAL_STRING("5", test_node->children[1]->value);

    TEST_MESSAGE("Function call print -> ok");
}