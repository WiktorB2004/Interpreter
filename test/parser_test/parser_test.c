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
    RUN_TEST(variable_declaration);
    RUN_TEST(variable_assignment);
    RUN_TEST(function_declaration);
    RUN_TEST(print_statement);
    RUN_TEST(conditional_statement);
    RUN_TEST(function_call);
    return UNITY_END();
}