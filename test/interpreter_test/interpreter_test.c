#include "unity.h"
#include "include/interpreter_test.h"

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
    // Variable handling
    RUN_TEST(variable_declaration);
    RUN_TEST(variable_accessing);
    RUN_TEST(variable_modification);
    RUN_TEST(variable_scoping);
    // Control flow
    RUN_TEST(if_statement);
    RUN_TEST(while_loop);
    RUN_TEST(function_call);
    return UNITY_END();
}