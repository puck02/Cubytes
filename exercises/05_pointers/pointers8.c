#include "unity.h"

// 比较函数类型定义
typedef int (*compare_func)(int, int);

int less_than(int a, int b) {
    // TODO: 实现这个函数
    
}

int greater_than(int a, int b) {
    // TODO: 实现这个函数
    
}

// TODO: 实现这个函数
// 使用比较函数对数组排序（冒泡排序）
// 提示：使用compare函数指针来决定排序顺序
void sort_array(int *arr, int size, compare_func compare) {
    // TODO: 实现这个函数
    
}
        }
    }
}

void setUp(void) {}
void tearDown(void) {}

void test_sort_ascending(void) {
    int arr[] = {5, 2, 8, 1, 9};
    sort_array(arr, 5, less_than);
    TEST_ASSERT_EQUAL_INT(1, arr[0]);
    TEST_ASSERT_EQUAL_INT(2, arr[1]);
    TEST_ASSERT_EQUAL_INT(5, arr[2]);
    TEST_ASSERT_EQUAL_INT(8, arr[3]);
    TEST_ASSERT_EQUAL_INT(9, arr[4]);
}

void test_sort_descending(void) {
    int arr[] = {5, 2, 8, 1, 9};
    sort_array(arr, 5, greater_than);
    TEST_ASSERT_EQUAL_INT(9, arr[0]);
    TEST_ASSERT_EQUAL_INT(8, arr[1]);
    TEST_ASSERT_EQUAL_INT(5, arr[2]);
    TEST_ASSERT_EQUAL_INT(2, arr[3]);
    TEST_ASSERT_EQUAL_INT(1, arr[4]);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sort_ascending);
    RUN_TEST(test_sort_descending);
    return UNITY_END();
}
