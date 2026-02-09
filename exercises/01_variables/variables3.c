#include "unity.h"

double calculate_average(int a, int b) {
    // TODO: 实现这个函数
    
}

float scale_percentage(int percentage) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_calculate_average(void) {
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 2.5, calculate_average(2, 3));
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 7.5, calculate_average(5, 10));
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 50.5, calculate_average(50, 51));
}

void test_scale_percentage(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.75, scale_percentage(75));
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.50, scale_percentage(50));
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.25, scale_percentage(25));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_calculate_average);
    RUN_TEST(test_scale_percentage);
    return UNITY_END();
}
