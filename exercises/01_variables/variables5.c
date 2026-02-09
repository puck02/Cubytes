#include "unity.h"

const double PI = 3.14159;

double get_pi(void) {
    // TODO: 实现这个函数
    
}

int double_to_int(double value) {
    // TODO: 实现这个函数
    
}

double int_to_double(int value) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_get_pi(void) {
    TEST_ASSERT_DOUBLE_WITHIN(0.00001, 3.14159, get_pi());
}

void test_double_to_int(void) {
    TEST_ASSERT_EQUAL_INT(3, double_to_int(3.14));
    TEST_ASSERT_EQUAL_INT(9, double_to_int(9.99));
    TEST_ASSERT_EQUAL_INT(-5, double_to_int(-5.7));
}

void test_int_to_double(void) {
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 42.0, int_to_double(42));
    TEST_ASSERT_DOUBLE_WITHIN(0.01, -10.0, int_to_double(-10));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_pi);
    RUN_TEST(test_double_to_int);
    RUN_TEST(test_int_to_double);
    return UNITY_END();
}
