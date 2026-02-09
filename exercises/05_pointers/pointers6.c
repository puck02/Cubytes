#include "unity.h"

// TODO: 实现这个函数
// 通过指针参数修改多个变量
// 将x和y都增加10
void increment_both(int *x, int *y) {
    // TODO: 实现这个函数
    
}

// TODO: 实现这个函数
// 计算数组的最大值和最小值
// 通过指针参数返回结果
void find_min_max(int *arr, int size, int *min, int *max) {
    // TODO: 实现这个函数
    
}
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}

void setUp(void) {}
void tearDown(void) {}

void test_increment_both(void) {
    int a = 5, b = 10;
    increment_both(&a, &b);
    TEST_ASSERT_EQUAL_INT(15, a);
    TEST_ASSERT_EQUAL_INT(20, b);
}

void test_find_min_max(void) {
    int arr[] = {5, 2, 8, 1, 9};
    int min, max;
    find_min_max(arr, 5, &min, &max);
    TEST_ASSERT_EQUAL_INT(1, min);
    TEST_ASSERT_EQUAL_INT(9, max);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_increment_both);
    RUN_TEST(test_find_min_max);
    return UNITY_END();
}
