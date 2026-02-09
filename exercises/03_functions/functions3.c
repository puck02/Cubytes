#include "unity.h"
#include <stdbool.h>

// TODO: 在这里声明函数原型（函数声明）
bool is_even(int n);

// TODO: 实现is_even函数
// 检查一个数是否是偶数
// 放在main函数之后定义

void setUp(void) {}
void tearDown(void) {}

void test_is_even(void) {
    // 这些测试需要is_even函数
    TEST_ASSERT_TRUE(is_even(4));
    TEST_ASSERT_FALSE(is_even(5));
    TEST_ASSERT_TRUE(is_even(0));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_is_even);
    return UNITY_END();
}

// TODO: 在这里定义is_even函数
bool is_even(int n) {
    return n % 2 == 0;
}
