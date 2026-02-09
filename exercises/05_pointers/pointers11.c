#include "unity.h"

// 学习目标：理解指针与数组的等价性
// 数组名实际上是指向第一个元素的指针

// TODO: 使用指针语法访问数组
// 返回数组中索引为index的元素
int get_by_pointer(int *arr, int index) {
    // TODO: 实现这个函数
    
}

// TODO: 使用数组语法访问指针
// 返回指针指向位置偏移index的元素
int get_by_bracket(int *ptr, int index) {
    // TODO: 实现这个函数
    
}

// TODO: 实现函数，验证两种方式等价
// 如果 arr[index] == *(arr + index)，返回1；否则返回0
int verify_equivalence(int *arr, int index) {
    // TODO: 实现这个函数
    
}

// TODO: 使用指针遍历数组求和
// 不使用数组下标，只使用指针算术
int sum_by_pointer(int *arr, int size) {
    // TODO: 实现这个函数
    
}
    return sum;
}

void setUp(void) {}
void tearDown(void) {}

void test_get_by_pointer(void) {
    int arr[] = {10, 20, 30, 40};
    TEST_ASSERT_EQUAL_INT(10, get_by_pointer(arr, 0));
    TEST_ASSERT_EQUAL_INT(30, get_by_pointer(arr, 2));
}

void test_get_by_bracket(void) {
    int arr[] = {10, 20, 30, 40};
    TEST_ASSERT_EQUAL_INT(20, get_by_bracket(arr, 1));
    TEST_ASSERT_EQUAL_INT(40, get_by_bracket(arr, 3));
}

void test_verify_equivalence(void) {
    int arr[] = {5, 15, 25, 35};
    TEST_ASSERT_EQUAL_INT(1, verify_equivalence(arr, 0));
    TEST_ASSERT_EQUAL_INT(1, verify_equivalence(arr, 2));
}

void test_sum_by_pointer(void) {
    int arr[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(15, sum_by_pointer(arr, 5));
    
    int arr2[] = {10, 20, 30};
    TEST_ASSERT_EQUAL_INT(60, sum_by_pointer(arr2, 3));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_by_pointer);
    RUN_TEST(test_get_by_bracket);
    RUN_TEST(test_verify_equivalence);
    RUN_TEST(test_sum_by_pointer);
    return UNITY_END();
}
