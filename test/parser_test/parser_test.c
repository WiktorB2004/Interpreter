#include "unity.h"
#include "include/parser_test.h"

// FIXME: Correctly free the output

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
    // Common combinations
    RUN_TEST(variable_declaration);
    RUN_TEST(variable_assignment);
    RUN_TEST(function_declaration);
    RUN_TEST(print_statement);
    RUN_TEST(conditional_statement);
    RUN_TEST(function_call);
    // Expressions
    RUN_TEST(arithmetic_expression);
    RUN_TEST(logic_expression);
    RUN_TEST(relational_expression);
    // Scopes
    RUN_TEST(function_scope);
    RUN_TEST(user_scope);
    RUN_TEST(if_scope);
    RUN_TEST(while_scope);
    return UNITY_END();
}