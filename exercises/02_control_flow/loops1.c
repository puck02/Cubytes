#include "unity.h"

// TODO: 实现这个函数
// 返回从1到n的所有数字的和
// 例如：sum_to_n(5) = 1 + 2 + 3 + 4 + 5 = 15
// 提示：使用for循环
int sum_to_n(int n) {
    // TODO: 实现这个函数
    
}
    return sum;
}

void setUp(void) {}
void tearDown(void) {}

void test_sum_to_n(void) {
    TEST_ASSERT_EQUAL_INT(15, sum_to_n(5));
    TEST_ASSERT_EQUAL_INT(55, sum_to_n(10));
    TEST_ASSERT_EQUAL_INT(1, sum_to_n(1));
    TEST_ASSERT_EQUAL_INT(0, sum_to_n(0));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sum_to_n);
    return UNITY_END();
}
