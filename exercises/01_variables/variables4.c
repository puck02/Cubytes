#include "unity.h"
#include <limits.h>

// TODO: 实现这些函数，返回正确的值

int get_char_max(void) {
    // TODO: 实现这个函数
    
}

int get_int_min(void) {
    // TODO: 实现这个函数
    
}

long get_long_max(void) {
    // 返回long类型的最大值（使用LONG_MAX常量）
    return LONG_MAX;
}

void setUp(void) {}
void tearDown(void) {}

void test_char_max(void) {
    TEST_ASSERT_EQUAL_INT(CHAR_MAX, get_char_max());
}

void test_int_min(void) {
    TEST_ASSERT_EQUAL_INT(INT_MIN, get_int_min());
}

void test_long_max(void) {
    TEST_ASSERT_EQUAL_INT64(LONG_MAX, get_long_max());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_char_max);
    RUN_TEST(test_int_min);
    RUN_TEST(test_long_max);
    return UNITY_END();
}
