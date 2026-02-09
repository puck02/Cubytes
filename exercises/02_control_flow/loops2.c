#include "unity.h"

// TODO: 实现这个函数
// 计算n的阶乘 (n!)
// 例如：factorial(5) = 5 * 4 * 3 * 2 * 1 = 120
// 提示：使用while循环
int factorial(int n) {
    // TODO: 实现这个函数
    
}
    return result;
}

void setUp(void) {}
void tearDown(void) {}

void test_factorial(void) {
    TEST_ASSERT_EQUAL_INT(1, factorial(0));
    TEST_ASSERT_EQUAL_INT(1, factorial(1));
    TEST_ASSERT_EQUAL_INT(120, factorial(5));
    TEST_ASSERT_EQUAL_INT(24, factorial(4));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_factorial);
    return UNITY_END();
}
