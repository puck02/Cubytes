#include "unity.h"

// TODO: 实现这个函数
// 返回数组中第n个元素的值（使用指针算术）
// 提示：ptr + n 指向第n个元素
int get_nth_element(int *ptr, int n) {
    // TODO: 实现这个函数
    
}

// TODO: 实现这个函数
// 设置数组中第n个元素的值（使用指针算术）
void set_nth_element(int *ptr, int n, int value) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_get_nth_element(void) {
    int arr[] = {10, 20, 30, 40, 50};
    TEST_ASSERT_EQUAL_INT(10, get_nth_element(arr, 0));
    TEST_ASSERT_EQUAL_INT(30, get_nth_element(arr, 2));
    TEST_ASSERT_EQUAL_INT(50, get_nth_element(arr, 4));
}

void test_set_nth_element(void) {
    int arr[] = {1, 2, 3, 4, 5};
    set_nth_element(arr, 0, 100);
    set_nth_element(arr, 2, 200);
    TEST_ASSERT_EQUAL_INT(100, arr[0]);
    TEST_ASSERT_EQUAL_INT(200, arr[2]);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_nth_element);
    RUN_TEST(test_set_nth_element);
    return UNITY_END();
}
