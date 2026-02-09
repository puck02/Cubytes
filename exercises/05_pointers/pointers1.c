#include "unity.h"

// TODO: 实现函数，交换两个整数的值
// 提示：使用指针参数
void swap(int *a, int *b) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_swap(void) {
    int x = 5, y = 10;
    swap(&x, &y);
    TEST_ASSERT_EQUAL_INT(10, x);
    TEST_ASSERT_EQUAL_INT(5, y);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_swap);
    return UNITY_END();
}
