#include "unity.h"
#include "include/lexer_test.h"

// Define setUp and tearDown functions
void setUp(void)
{
    // setup code
}

void tearDown(void)
{
    // teardown code
}

int main(void)
{
    UNITY_BEGIN();
    // Edge cases
    RUN_TEST(empty_input);
    RUN_TEST(whitespace_input);
    RUN_TEST(newline_input);
    RUN_TEST(mixed_edge_cases);
    TEST_MESSAGE("Lexer Edge Cases -> ok");
    // Tokens
    RUN_TEST(tokens_id);
    RUN_TEST(tokens_v_type);
    RUN_TEST(tokens_val);
    RUN_TEST(tokens_t_val);
    RUN_TEST(tokens_keywords);
    RUN_TEST(tokens_operators);
    RUN_TEST(tokens_special);
    TEST_MESSAGE("Lexer Tokens -> ok");
    // Common combinations
    RUN_TEST(variable_declaration);
    RUN_TEST(variable_assignment);
    RUN_TEST(function_declaration);
    RUN_TEST(while_loop);
    RUN_TEST(conditional_statement);
    RUN_TEST(expression);
    TEST_MESSAGE("Lexer Common Cominations -> ok");
    return UNITY_END();
}