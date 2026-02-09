#include "unity.h"

// TODO: 实现这个函数
// 统计数组中有多少个偶数
// 提示：使用for循环，使用%运算符检查偶数
int count_even(int arr[], int size) {
    // TODO: 实现这个函数
    
}
    }
    return count;
}

// TODO: 实现这个函数
// 找到第一个负数的索引，如果没有返回-1
// 提示：使用循环和break语句
int find_first_negative(int arr[], int size) {
    // TODO: 实现这个函数
    
}
    }
    return -1;
}

void setUp(void) {}
void tearDown(void) {}

void test_count_even(void) {
    int arr1[] = {1, 2, 3, 4, 5, 6};
    TEST_ASSERT_EQUAL_INT(3, count_even(arr1, 6));
    
    int arr2[] = {1, 3, 5, 7};
    TEST_ASSERT_EQUAL_INT(0, count_even(arr2, 4));
    
    int arr3[] = {2, 4, 6, 8};
    TEST_ASSERT_EQUAL_INT(4, count_even(arr3, 4));
}

void test_find_first_negative(void) {
    int arr1[] = {1, 2, -3, 4, -5};
    TEST_ASSERT_EQUAL_INT(2, find_first_negative(arr1, 5));
    
    int arr2[] = {1, 2, 3, 4};
    TEST_ASSERT_EQUAL_INT(-1, find_first_negative(arr2, 4));
    
    int arr3[] = {-1, 2, 3};
    TEST_ASSERT_EQUAL_INT(0, find_first_negative(arr3, 3));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_count_even);
    RUN_TEST(test_find_first_negative);
    return UNITY_END();
}
