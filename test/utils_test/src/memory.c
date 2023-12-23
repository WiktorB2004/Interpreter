#include "unity.h"
#include "../include/utils_test.h"
#include "../include/memory.h"
#include "../include/parser.h"
#include "../include/utils/expression_eval.h"

void memory_manipulation(void)
{
    ScopeStack memory;
    Variable *var1, *var2;
    init_ScopeStack(&memory, 100);
    push_scope(&memory, 100);

    add_variable(&memory, "int", "testVar", create_ASTNode(NODE_VAL, "testVal"), NULL);
    push_scope(&memory, 50);
    add_variable(&memory, "int", "scopeTest", create_ASTNode(NODE_VAL, "testVal2"), NULL);
    var1 = find_variable(&memory, "testVar");
    var2 = find_variable(&memory, "scopeTest");
    TEST_ASSERT_EQUAL_STRING(var1->value->value, "testVal");
    TEST_ASSERT_EQUAL_STRING(var2->value->value, "testVal2");
    pop_scope(&memory);
    var1 = find_variable(&memory, "testVar");
    var2 = find_variable(&memory, "scopeTest");
    TEST_ASSERT_EQUAL_STRING(var1->value->value, "testVal");
    TEST_ASSERT_NULL(var2);
}
