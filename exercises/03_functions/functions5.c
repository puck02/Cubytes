#include "unity.h"

const double PI = 3.14159;

double circle_area(double radius) {
    // TODO: 实现这个函数
    
}

int is_positive(int n) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_circle_area(void) {
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 3.14, circle_area(1.0));
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 28.27, circle_area(3.0));
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 78.54, circle_area(5.0));
}

void test_is_positive(void) {
    TEST_ASSERT_EQUAL_INT(1, is_positive(5));
    TEST_ASSERT_EQUAL_INT(0, is_positive(0));
    TEST_ASSERT_EQUAL_INT(0, is_positive(-5));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_circle_area);
    RUN_TEST(test_is_positive);
    return UNITY_END();
}
