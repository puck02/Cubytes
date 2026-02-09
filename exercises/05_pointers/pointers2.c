#include "unity.h"

// TODO: 实现这个函数
// 通过指针修改变量的值
// ptr: 指向int的指针, value: 要设置的新值
void set_value(int *ptr, int value) {
    // TODO: 实现这个函数
    
}

// TODO: 实现这个函数
// 通过指针读取变量的值
int get_value(int *ptr) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_set_value(void) {
    int x = 10;
    set_value(&x, 20);
    TEST_ASSERT_EQUAL_INT(20, x);
}

void test_get_value(void) {
    int x = 42;
    TEST_ASSERT_EQUAL_INT(42, get_value(&x));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_set_value);
    RUN_TEST(test_get_value);
    return UNITY_END();
}
