#include "unity.h"
#include "stdlib.h"
#include "../include/lexer_test.h"
#include "../../include/lexer.h"

// FIXME: Create test groups instead of executing multiple tests inside one test case

void tokens_id(void)
{
    int num_tokens;
    char *input = "s hello_world num1 num11 num123n hello1_world2";
    Token *output = lexer(input, &num_tokens);
    for (int i = 0; i < num_tokens - 1; i++)
    {
        TEST_ASSERT_EQUAL_INT(ID, output[i].type);
    }
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}

void tokens_v_type(void)
{
    int num_tokens;
    char *input = "int char string";
    Token *output = lexer(input, &num_tokens);
    for (int i = 0; i < num_tokens - 1; i++)
    {
        TEST_ASSERT_EQUAL_INT(V_TYPE, output[i].type);
    }
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}

void tokens_val(void)
{
    int num_tokens;
    // Variable declaration
    char *input1 = "int val_1 = 123";
    Token *output = lexer(input1, &num_tokens);
    TEST_ASSERT_EQUAL_INT(VAL, output[3].type);
    TEST_ASSERT_EQUAL_STRING("123", output[3].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[4].type);
    // Variable assignment
    char *input2 = "val2 = -52";
    output = lexer(input2, &num_tokens);
    TEST_ASSERT_EQUAL_INT(VAL, output[2].type);
    TEST_ASSERT_EQUAL_STRING("-52", output[2].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[3].type);
    char *input3 = "val2 = 1.5";
    output = lexer(input3, &num_tokens);
    TEST_ASSERT_EQUAL_INT(VAL, output[2].type);
    TEST_ASSERT_EQUAL_STRING("1.5", output[2].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[3].type);
    free(output);
}

void tokens_t_val(void)
{
    int num_tokens;
    // Variable declaration
    char *input1 = "int val_1 = \"hello World 123 \"";
    Token *output = lexer(input1, &num_tokens);
    TEST_ASSERT_EQUAL_INT(T_VAL, output[3].type);
    TEST_ASSERT_EQUAL_STRING("\"hello World 123 \"", output[3].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[4].type);
    // Variable assignment
    char *input2 = "val2 = \"-52\"";
    output = lexer(input2, &num_tokens);
    TEST_ASSERT_EQUAL_INT(T_VAL, output[2].type);
    TEST_ASSERT_EQUAL_STRING("\"-52\"", output[2].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[3].type);
    char *input3 = "val3 = \"1.5\"";
    output = lexer(input3, &num_tokens);
    TEST_ASSERT_EQUAL_INT(T_VAL, output[2].type);
    TEST_ASSERT_EQUAL_STRING("\"1.5\"", output[2].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[3].type);
    char *input4 = "val4 = \".,?!@#$%^&*()-_+=;:<>/\\|[]{}~\"";
    output = lexer(input4, &num_tokens);
    TEST_ASSERT_EQUAL_INT(T_VAL, output[2].type);
    TEST_ASSERT_EQUAL_STRING("\".,?!@#$%^&*()-_+=;:<>/\\|[]{}~\"", output[2].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[3].type);
    free(output);
}

void tokens_keywords(void)
{
    int num_tokens;
    char *input1 = "IF ELSE WHILE DEF PRINT";
    Token *output = lexer(input1, &num_tokens);
    for (int i = 0; i < num_tokens - 1; i++)
    {
        TEST_ASSERT_EQUAL_INT(KEYWORD, output[i].type);
    }
    TEST_ASSERT_EQUAL_STRING("IF", output[0].value);
    TEST_ASSERT_EQUAL_STRING("ELSE", output[1].value);
    TEST_ASSERT_EQUAL_STRING("WHILE", output[2].value);
    TEST_ASSERT_EQUAL_STRING("DEF", output[3].value);
    TEST_ASSERT_EQUAL_STRING("PRINT", output[4].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}

void tokens_operators(void)
{
    int num_tokens;
    // ARITHMETIC
    char *input1 = "+ - / *";
    Token *output = lexer(input1, &num_tokens);
    for (int i = 0; i < num_tokens - 1; i++)
    {
        TEST_ASSERT_EQUAL_INT(ARITH_OP, output[i].type);
    }
    TEST_ASSERT_EQUAL_STRING("+", output[0].value);
    TEST_ASSERT_EQUAL_STRING("-", output[1].value);
    TEST_ASSERT_EQUAL_STRING("/", output[2].value);
    TEST_ASSERT_EQUAL_STRING("*", output[3].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    // RELATIONAL
    char *input2 = "> >= < <= == !=";
    output = lexer(input2, &num_tokens);
    for (int i = 0; i < num_tokens - 1; i++)
    {
        TEST_ASSERT_EQUAL_INT(RELAT_OP, output[i].type);
    }
    TEST_ASSERT_EQUAL_STRING(">", output[0].value);
    TEST_ASSERT_EQUAL_STRING(">=", output[1].value);
    TEST_ASSERT_EQUAL_STRING("<", output[2].value);
    TEST_ASSERT_EQUAL_STRING("<=", output[3].value);
    TEST_ASSERT_EQUAL_STRING("==", output[4].value);
    TEST_ASSERT_EQUAL_STRING("!=", output[5].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    // LOGIC
    char *input3 = "&& ||";
    output = lexer(input3, &num_tokens);
    TEST_ASSERT_EQUAL_INT(LOGIC_OP, output[0].type);
    TEST_ASSERT_EQUAL_STRING("&&", output[0].value);
    TEST_ASSERT_EQUAL_INT(LOGIC_OP, output[1].type);
    TEST_ASSERT_EQUAL_STRING("||", output[1].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}

void tokens_special(void)
{
    int num_tokens;
    // ARITHMETIC
    char *input1 = "= ( ) [ ] { } , ; ->";
    Token *output = lexer(input1, &num_tokens);
    TEST_ASSERT_EQUAL_INT(ASSIGN, output[0].type);
    TEST_ASSERT_EQUAL_STRING("=", output[0].value);
    TEST_ASSERT_EQUAL_INT(O_PAREN, output[1].type);
    TEST_ASSERT_EQUAL_STRING("(", output[1].value);
    TEST_ASSERT_EQUAL_INT(C_PAREN, output[2].type);
    TEST_ASSERT_EQUAL_STRING(")", output[2].value);
    TEST_ASSERT_EQUAL_INT(LIST_B, output[3].type);
    TEST_ASSERT_EQUAL_STRING("[", output[3].value);
    TEST_ASSERT_EQUAL_INT(LIST_E, output[4].type);
    TEST_ASSERT_EQUAL_STRING("]", output[4].value);
    TEST_ASSERT_EQUAL_INT(O_BRACKET, output[5].type);
    TEST_ASSERT_EQUAL_STRING("{", output[5].value);
    TEST_ASSERT_EQUAL_INT(C_BRACKET, output[6].type);
    TEST_ASSERT_EQUAL_STRING("}", output[6].value);
    TEST_ASSERT_EQUAL_INT(COMMA, output[7].type);
    TEST_ASSERT_EQUAL_STRING(",", output[7].value);
    TEST_ASSERT_EQUAL_INT(SEMI, output[8].type);
    TEST_ASSERT_EQUAL_STRING(";", output[8].value);
    TEST_ASSERT_EQUAL_INT(R_TYPE, output[9].type);
    TEST_ASSERT_EQUAL_STRING("->", output[9].value);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}
