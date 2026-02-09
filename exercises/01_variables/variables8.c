#include "unity.h"

int round_to_int(double value) {
    // TODO: 实现这个函数
    
}

double celsius_to_fahrenheit(int celsius) {
    // TODO: 实现这个函数
    
}

double fahrenheit_to_celsius(int fahrenheit) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_round_to_int(void) {
    TEST_ASSERT_EQUAL_INT(3, round_to_int(2.5));
    TEST_ASSERT_EQUAL_INT(4, round_to_int(3.7));
    TEST_ASSERT_EQUAL_INT(10, round_to_int(9.6));
    TEST_ASSERT_EQUAL_INT(2, round_to_int(2.3));
}

void test_celsius_to_fahrenheit(void) {
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 32.0, celsius_to_fahrenheit(0));
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 68.0, celsius_to_fahrenheit(20));
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 98.6, celsius_to_fahrenheit(37));
}

void test_fahrenheit_to_celsius(void) {
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.0, fahrenheit_to_celsius(32));
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 20.0, fahrenheit_to_celsius(68));
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 100.0, fahrenheit_to_celsius(212));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_round_to_int);
    RUN_TEST(test_celsius_to_fahrenheit);
    RUN_TEST(test_fahrenheit_to_celsius);
    return UNITY_END();
}
