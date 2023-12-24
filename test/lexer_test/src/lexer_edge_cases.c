#include "unity.h"
#include "stdlib.h"
#include "../include/lexer_test.h"
#include "../../../include/lexer.h"

void empty_input(void)
{
    int num_tokens;
    const char *input = "";

    Token *output = lexer(input, &num_tokens);

    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[0].type);

    free(output);
}

void whitespace_input(void)
{
    int num_tokens;
    const char *input = "     ";

    Token *output = lexer(input, &num_tokens);

    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[0].type);
    free(output);
}

void newline_input(void)
{
    int num_tokens;
    const char *input = "\n\n\n\n";

    Token *output = lexer(input, &num_tokens);

    TEST_ASSERT_NOT_NULL(output);
    for (int i = 0; i < num_tokens - 1; i++)
    {
        TEST_ASSERT_EQUAL_INT(TOKEN_Newline, output[i].type);
    }
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[num_tokens - 1].type);
    free(output);
}

void mixed_edge_cases(void)
{
    int num_tokens;
    const char *input = "\n \n ";

    Token *output = lexer(input, &num_tokens);
    TEST_ASSERT_NOT_NULL(output);

    TEST_ASSERT_EQUAL_INT(TOKEN_Newline, output[0].type);
    TEST_ASSERT_EQUAL_INT(TOKEN_Newline, output[1].type);
    TEST_ASSERT_EQUAL_INT(TOKEN_EOF, output[2].type);
    free(output);
}
