#include "unity.h"

// 函数指针示例
int add(int a, int b) {
    // TODO: 实现这个函数
    
}

int subtract(int a, int b) {
    // TODO: 实现这个函数
    
}

// TODO: 实现这个函数
// 使用函数指针调用函数
// operation: 函数指针（指向接受两个int参数并返回int的函数）
int apply_operation(int (*operation)(int, int), int a, int b) {
    return operation(a, b);
}

void setUp(void) {}
void tearDown(void) {}

void test_apply_operation(void) {
    TEST_ASSERT_EQUAL_INT(8, apply_operation(add, 5, 3));
    TEST_ASSERT_EQUAL_INT(2, apply_operation(subtract, 5, 3));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_apply_operation);
    return UNITY_END();
}
