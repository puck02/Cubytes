#include "unity.h"

// TODO: 实现这个函数
// 使用指针遍历数组并计算和
// 提示：可以用ptr[i]或*(ptr+i)访问元素
int sum_with_pointer(int *ptr, int size) {
    // TODO: 实现这个函数
    
}
    return sum;
}

// TODO: 实现这个函数
// 使用指针找到数组中的最小值
int find_min_with_pointer(int *ptr, int size) {
    // TODO: 实现这个函数
    
}
    }
    return min;
}

void setUp(void) {}
void tearDown(void) {}

void test_sum_with_pointer(void) {
    int arr[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(15, sum_with_pointer(arr, 5));
}

void test_find_min_with_pointer(void) {
    int arr[] = {5, 2, 8, 1, 9};
    TEST_ASSERT_EQUAL_INT(1, find_min_with_pointer(arr, 5));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sum_with_pointer);
    RUN_TEST(test_find_min_with_pointer);
    return UNITY_END();
}
