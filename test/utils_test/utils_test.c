#include "unity.h"
#include "include/utils_test.h"

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
    // Expression evaluation
    RUN_TEST(expression_edge_cases);
    RUN_TEST(int_expression_eval);
    RUN_TEST(float_expression_eval);
    // Memory handling
    RUN_TEST(memory_manipulation);
    return UNITY_END();
}