#include "unity.h"

// 学习目标：理解递归的基本概念
// 递归函数会调用自己来解决问题

// TODO: 实现递归求和函数
// 计算 1 + 2 + 3 + ... + n
// 思考：基础情况是什么？递归情况如何表达？
int sum_recursive(int n) {
    // TODO: 实现这个函数
    
}

// TODO: 实现递归倒数乘积函数
// 计算从n递减到1的乘积：countdown_product(5) = 5*4*3*2*1 = 120
// 思考：这和阶乘(factorial)类似
int countdown_product(int n) {
    // TODO: 实现这个函数
    
}

// TODO: 实现递归计数函数
// 计算一个数有多少位数字
// 例如：count_digits(1234) = 4
int count_digits(int n) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_sum_recursive(void) {
    TEST_ASSERT_EQUAL_INT(0, sum_recursive(0));
    TEST_ASSERT_EQUAL_INT(1, sum_recursive(1));
    TEST_ASSERT_EQUAL_INT(15, sum_recursive(5));
    TEST_ASSERT_EQUAL_INT(55, sum_recursive(10));
}

void test_countdown_product(void) {
    TEST_ASSERT_EQUAL_INT(1, countdown_product(1));
    TEST_ASSERT_EQUAL_INT(120, countdown_product(5));
    TEST_ASSERT_EQUAL_INT(24, countdown_product(4));
}

void test_count_digits(void) {
    TEST_ASSERT_EQUAL_INT(1, count_digits(5));
    TEST_ASSERT_EQUAL_INT(2, count_digits(42));
    TEST_ASSERT_EQUAL_INT(4, count_digits(1234));
    TEST_ASSERT_EQUAL_INT(5, count_digits(98765));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sum_recursive);
    RUN_TEST(test_countdown_product);
    RUN_TEST(test_count_digits);
    return UNITY_END();
}
