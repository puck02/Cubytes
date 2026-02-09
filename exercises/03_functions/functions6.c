#include "unity.h"

// 全局变量
int global_counter = 0;

// TODO: 实现这个函数
// 增加global_counter并返回新值
int increment_counter(void) {
    // TODO: 实现这个函数
    
}

// TODO: 实现这个函数
// 重置global_counter为0
void reset_counter(void) {
    // TODO: 实现这个函数
    
}

void setUp(void) {
    reset_counter();
}

void tearDown(void) {}

void test_increment(void) {
    TEST_ASSERT_EQUAL_INT(1, increment_counter());
    TEST_ASSERT_EQUAL_INT(2, increment_counter());
    TEST_ASSERT_EQUAL_INT(3, increment_counter());
}

void test_reset(void) {
    increment_counter();
    increment_counter();
    reset_counter();
    TEST_ASSERT_EQUAL_INT(0, global_counter);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_increment);
    RUN_TEST(test_reset);
    return UNITY_END();
}
