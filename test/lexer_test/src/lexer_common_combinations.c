#include "unity.h"
#include "stdlib.h"
#include "../include/lexer_test.h"
#include "../../include/lexer.h"

// FIXME: Create test groups instead of executing multiple tests inside one test case

void variable_declaration(void)
{
    int num_tokens;
    char *input1 = "int num1 = -1.5;";
    Token *output = lexer(input1, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(V_TYPE, output[0].type);
    TEST_ASSERT_EQUAL_INT(ID, output[1].type);
    TEST_ASSERT_EQUAL_INT(ASSIGN, output[2].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[3].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("int", output[0].value);
    TEST_ASSERT_EQUAL_STRING("num1", output[1].value);
    TEST_ASSERT_EQUAL_STRING("=", output[2].value);
    TEST_ASSERT_EQUAL_STRING("-1.5", output[3].value);

    TEST_ASSERT_EQUAL_INT(SEMI, output[num_tokens - 2].type);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    char *input2 = "string str = \"Hello World!\";";
    output = lexer(input2, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(V_TYPE, output[0].type);
    TEST_ASSERT_EQUAL_INT(ID, output[1].type);
    TEST_ASSERT_EQUAL_INT(ASSIGN, output[2].type);
    TEST_ASSERT_EQUAL_INT(T_VAL, output[3].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("string", output[0].value);
    TEST_ASSERT_EQUAL_STRING("str", output[1].value);
    TEST_ASSERT_EQUAL_STRING("=", output[2].value);
    TEST_ASSERT_EQUAL_STRING("\"Hello World!\"", output[3].value);

    TEST_ASSERT_EQUAL_INT(SEMI, output[num_tokens - 2].type);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    char *input3 = "char chr = \'c\';";
    output = lexer(input3, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(V_TYPE, output[0].type);
    TEST_ASSERT_EQUAL_INT(ID, output[1].type);
    TEST_ASSERT_EQUAL_INT(ASSIGN, output[2].type);
    TEST_ASSERT_EQUAL_INT(T_VAL, output[3].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("char", output[0].value);
    TEST_ASSERT_EQUAL_STRING("chr", output[1].value);
    TEST_ASSERT_EQUAL_STRING("=", output[2].value);
    TEST_ASSERT_EQUAL_STRING("\'c\'", output[3].value);

    TEST_ASSERT_EQUAL_INT(SEMI, output[num_tokens - 2].type);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    char *input4 = "int num2 = num1;";
    output = lexer(input4, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(V_TYPE, output[0].type);
    TEST_ASSERT_EQUAL_INT(ID, output[1].type);
    TEST_ASSERT_EQUAL_INT(ASSIGN, output[2].type);
    TEST_ASSERT_EQUAL_INT(ID, output[3].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("int", output[0].value);
    TEST_ASSERT_EQUAL_STRING("num2", output[1].value);
    TEST_ASSERT_EQUAL_STRING("=", output[2].value);
    TEST_ASSERT_EQUAL_STRING("num1", output[3].value);

    TEST_ASSERT_EQUAL_INT(SEMI, output[num_tokens - 2].type);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}

void variable_assignment(void)
{
    int num_tokens;
    char *input1 = "num1 = -1.5;";
    Token *output = lexer(input1, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(ID, output[0].type);
    TEST_ASSERT_EQUAL_INT(ASSIGN, output[1].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[2].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("num1", output[0].value);
    TEST_ASSERT_EQUAL_STRING("=", output[1].value);
    TEST_ASSERT_EQUAL_STRING("-1.5", output[2].value);

    TEST_ASSERT_EQUAL_INT(SEMI, output[num_tokens - 2].type);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    char *input2 = "str = \"Hello World!\";";
    output = lexer(input2, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(ID, output[0].type);
    TEST_ASSERT_EQUAL_INT(ASSIGN, output[1].type);
    TEST_ASSERT_EQUAL_INT(T_VAL, output[2].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("str", output[0].value);
    TEST_ASSERT_EQUAL_STRING("=", output[1].value);
    TEST_ASSERT_EQUAL_STRING("\"Hello World!\"", output[2].value);

    TEST_ASSERT_EQUAL_INT(SEMI, output[num_tokens - 2].type);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    char *input3 = "chr = \'c\';";
    output = lexer(input3, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(ID, output[0].type);
    TEST_ASSERT_EQUAL_INT(ASSIGN, output[1].type);
    TEST_ASSERT_EQUAL_INT(T_VAL, output[2].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("chr", output[0].value);
    TEST_ASSERT_EQUAL_STRING("=", output[1].value);
    TEST_ASSERT_EQUAL_STRING("\'c\'", output[2].value);

    TEST_ASSERT_EQUAL_INT(SEMI, output[num_tokens - 2].type);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}

void function_declaration(void)
{
    int num_tokens;
    char *input = "DEF func -> int (param_1, 123, \"text\") {}";
    Token *output = lexer(input, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(KEYWORD, output[0].type);
    TEST_ASSERT_EQUAL_INT(ID, output[1].type);
    TEST_ASSERT_EQUAL_INT(R_TYPE, output[2].type);
    TEST_ASSERT_EQUAL_INT(V_TYPE, output[3].type);
    TEST_ASSERT_EQUAL_INT(O_PAREN, output[4].type);
    TEST_ASSERT_EQUAL_INT(ID, output[5].type);
    TEST_ASSERT_EQUAL_INT(COMMA, output[6].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[7].type);
    TEST_ASSERT_EQUAL_INT(COMMA, output[8].type);
    TEST_ASSERT_EQUAL_INT(T_VAL, output[9].type);
    TEST_ASSERT_EQUAL_INT(C_PAREN, output[10].type);
    TEST_ASSERT_EQUAL_INT(O_BRACKET, output[11].type);
    TEST_ASSERT_EQUAL_INT(C_BRACKET, output[12].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("DEF", output[0].value);
    TEST_ASSERT_EQUAL_STRING("func", output[1].value);
    TEST_ASSERT_EQUAL_STRING("->", output[2].value);
    TEST_ASSERT_EQUAL_STRING("int", output[3].value);
    TEST_ASSERT_EQUAL_STRING("(", output[4].value);
    TEST_ASSERT_EQUAL_STRING("param_1", output[5].value);
    TEST_ASSERT_EQUAL_STRING(",", output[6].value);
    TEST_ASSERT_EQUAL_STRING("123", output[7].value);
    TEST_ASSERT_EQUAL_STRING(",", output[8].value);
    TEST_ASSERT_EQUAL_STRING("\"text\"", output[9].value);
    TEST_ASSERT_EQUAL_STRING(")", output[10].value);
    TEST_ASSERT_EQUAL_STRING("{", output[11].value);
    TEST_ASSERT_EQUAL_STRING("}", output[12].value);

    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}

void while_loop(void)
{
    int num_tokens;
    char *input = "WHILE (num1 >= \"5\" && num2 < 0) {}";
    Token *output = lexer(input, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(KEYWORD, output[0].type);
    TEST_ASSERT_EQUAL_INT(O_PAREN, output[1].type);
    TEST_ASSERT_EQUAL_INT(ID, output[2].type);
    TEST_ASSERT_EQUAL_INT(RELAT_OP, output[3].type);
    TEST_ASSERT_EQUAL_INT(T_VAL, output[4].type);
    TEST_ASSERT_EQUAL_INT(LOGIC_OP, output[5].type);
    TEST_ASSERT_EQUAL_INT(ID, output[6].type);
    TEST_ASSERT_EQUAL_INT(RELAT_OP, output[7].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[8].type);
    TEST_ASSERT_EQUAL_INT(C_PAREN, output[9].type);
    TEST_ASSERT_EQUAL_INT(O_BRACKET, output[10].type);
    TEST_ASSERT_EQUAL_INT(C_BRACKET, output[11].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("WHILE", output[0].value);
    TEST_ASSERT_EQUAL_STRING("(", output[1].value);
    TEST_ASSERT_EQUAL_STRING("num1", output[2].value);
    TEST_ASSERT_EQUAL_STRING(">=", output[3].value);
    TEST_ASSERT_EQUAL_STRING("\"5\"", output[4].value);
    TEST_ASSERT_EQUAL_STRING("&&", output[5].value);
    TEST_ASSERT_EQUAL_STRING("num2", output[6].value);
    TEST_ASSERT_EQUAL_STRING("<", output[7].value);
    TEST_ASSERT_EQUAL_STRING("0", output[8].value);
    TEST_ASSERT_EQUAL_STRING(")", output[9].value);
    TEST_ASSERT_EQUAL_STRING("{", output[10].value);
    TEST_ASSERT_EQUAL_STRING("}", output[11].value);

    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}

void conditional_statement(void)
{
    int num_tokens;
    char *input = "IF (hello != world || wlang != the_best) {} ELSE {}";
    Token *output = lexer(input, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(KEYWORD, output[0].type);
    TEST_ASSERT_EQUAL_INT(O_PAREN, output[1].type);
    TEST_ASSERT_EQUAL_INT(ID, output[2].type);
    TEST_ASSERT_EQUAL_INT(RELAT_OP, output[3].type);
    TEST_ASSERT_EQUAL_INT(ID, output[4].type);
    TEST_ASSERT_EQUAL_INT(LOGIC_OP, output[5].type);
    TEST_ASSERT_EQUAL_INT(ID, output[6].type);
    TEST_ASSERT_EQUAL_INT(RELAT_OP, output[7].type);
    TEST_ASSERT_EQUAL_INT(ID, output[8].type);
    TEST_ASSERT_EQUAL_INT(C_PAREN, output[9].type);
    TEST_ASSERT_EQUAL_INT(O_BRACKET, output[10].type);
    TEST_ASSERT_EQUAL_INT(C_BRACKET, output[11].type);
    TEST_ASSERT_EQUAL_INT(KEYWORD, output[12].type);
    TEST_ASSERT_EQUAL_INT(O_BRACKET, output[13].type);
    TEST_ASSERT_EQUAL_INT(C_BRACKET, output[14].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("IF", output[0].value);
    TEST_ASSERT_EQUAL_STRING("(", output[1].value);
    TEST_ASSERT_EQUAL_STRING("hello", output[2].value);
    TEST_ASSERT_EQUAL_STRING("!=", output[3].value);
    TEST_ASSERT_EQUAL_STRING("world", output[4].value);
    TEST_ASSERT_EQUAL_STRING("||", output[5].value);
    TEST_ASSERT_EQUAL_STRING("wlang", output[6].value);
    TEST_ASSERT_EQUAL_STRING("!=", output[7].value);
    TEST_ASSERT_EQUAL_STRING("the_best", output[8].value);
    TEST_ASSERT_EQUAL_STRING(")", output[9].value);
    TEST_ASSERT_EQUAL_STRING("{", output[10].value);
    TEST_ASSERT_EQUAL_STRING("}", output[11].value);
    TEST_ASSERT_EQUAL_STRING("ELSE", output[12].value);
    TEST_ASSERT_EQUAL_STRING("{", output[13].value);
    TEST_ASSERT_EQUAL_STRING("}", output[14].value);

    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}

void expression(void)
{
    int num_tokens;
    char *input1 = "1 + num1 * (5 + 8)";
    Token *output = lexer(input1, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(VAL, output[0].type);
    TEST_ASSERT_EQUAL_INT(ARITH_OP, output[1].type);
    TEST_ASSERT_EQUAL_INT(ID, output[2].type);
    TEST_ASSERT_EQUAL_INT(ARITH_OP, output[3].type);
    TEST_ASSERT_EQUAL_INT(O_PAREN, output[4].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[5].type);
    TEST_ASSERT_EQUAL_INT(ARITH_OP, output[6].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[7].type);
    TEST_ASSERT_EQUAL_INT(C_PAREN, output[8].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("1", output[0].value);
    TEST_ASSERT_EQUAL_STRING("+", output[1].value);
    TEST_ASSERT_EQUAL_STRING("num1", output[2].value);
    TEST_ASSERT_EQUAL_STRING("*", output[3].value);
    TEST_ASSERT_EQUAL_STRING("(", output[4].value);
    TEST_ASSERT_EQUAL_STRING("5", output[5].value);
    TEST_ASSERT_EQUAL_STRING("+", output[6].value);
    TEST_ASSERT_EQUAL_STRING("8", output[7].value);
    TEST_ASSERT_EQUAL_STRING(")", output[8].value);

    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    char *input2 = "-5 + test > 38 * word";
    output = lexer(input2, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(VAL, output[0].type);
    TEST_ASSERT_EQUAL_INT(ARITH_OP, output[1].type);
    TEST_ASSERT_EQUAL_INT(ID, output[2].type);
    TEST_ASSERT_EQUAL_INT(RELAT_OP, output[3].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[4].type);
    TEST_ASSERT_EQUAL_INT(ARITH_OP, output[5].type);
    TEST_ASSERT_EQUAL_INT(ID, output[6].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("-5", output[0].value);
    TEST_ASSERT_EQUAL_STRING("+", output[1].value);
    TEST_ASSERT_EQUAL_STRING("test", output[2].value);
    TEST_ASSERT_EQUAL_STRING(">", output[3].value);
    TEST_ASSERT_EQUAL_STRING("38", output[4].value);
    TEST_ASSERT_EQUAL_STRING("*", output[5].value);
    TEST_ASSERT_EQUAL_STRING("word", output[6].value);

    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    char *input3 = "(-5 > hello || 2 + 2 == 4) && 5 != 3";
    output = lexer(input3, &num_tokens);
    // Types
    TEST_ASSERT_EQUAL_INT(O_PAREN, output[0].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[1].type);
    TEST_ASSERT_EQUAL_INT(RELAT_OP, output[2].type);
    TEST_ASSERT_EQUAL_INT(ID, output[3].type);
    TEST_ASSERT_EQUAL_INT(LOGIC_OP, output[4].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[5].type);
    TEST_ASSERT_EQUAL_INT(ARITH_OP, output[6].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[7].type);
    TEST_ASSERT_EQUAL_INT(RELAT_OP, output[8].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[9].type);
    TEST_ASSERT_EQUAL_INT(C_PAREN, output[10].type);
    TEST_ASSERT_EQUAL_INT(LOGIC_OP, output[11].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[12].type);
    TEST_ASSERT_EQUAL_INT(RELAT_OP, output[13].type);
    TEST_ASSERT_EQUAL_INT(VAL, output[14].type);
    // Values
    TEST_ASSERT_EQUAL_STRING("(", output[0].value);
    TEST_ASSERT_EQUAL_STRING("-5", output[1].value);
    TEST_ASSERT_EQUAL_STRING(">", output[2].value);
    TEST_ASSERT_EQUAL_STRING("hello", output[3].value);
    TEST_ASSERT_EQUAL_STRING("||", output[4].value);
    TEST_ASSERT_EQUAL_STRING("2", output[5].value);
    TEST_ASSERT_EQUAL_STRING("+", output[6].value);
    TEST_ASSERT_EQUAL_STRING("2", output[7].value);
    TEST_ASSERT_EQUAL_STRING("==", output[8].value);
    TEST_ASSERT_EQUAL_STRING("4", output[9].value);
    TEST_ASSERT_EQUAL_STRING(")", output[10].value);
    TEST_ASSERT_EQUAL_STRING("&&", output[11].value);
    TEST_ASSERT_EQUAL_STRING("5", output[12].value);
    TEST_ASSERT_EQUAL_STRING("!=", output[13].value);
    TEST_ASSERT_EQUAL_STRING("3", output[14].value);

    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}