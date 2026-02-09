#include "unity.h"

// 学习目标：理解 continue 语句的作用
// continue 会跳过当前迭代，继续下一次循环

// TODO: 实现函数，求和时跳过偶数
// 只对奇数求和：1 + 3 + 5 + ... (所有 <= n 的奇数)
int sum_odd_numbers(int n) {
    // TODO: 实现这个函数
    
}
    return sum;
}

// TODO: 实现函数，计数非零元素
// 跳过值为0的元素
int count_non_zero(int arr[], int size) {
    // TODO: 实现这个函数
    
}
    return count;
}

// TODO: 实现函数，求数组中正数的和
// 使用continue跳过负数和零
int sum_positive(int arr[], int size) {
    // TODO: 实现这个函数
    
}
    return sum;
}

// TODO: 实现函数，跳过3的倍数求和
// 1+2+4+5+7+8+10+... (跳过3,6,9...)
int sum_skip_multiples_of_3(int n) {
    // TODO: 实现这个函数
    
}
    return sum;
}

void setUp(void) {}
void tearDown(void) {}

void test_sum_odd_numbers(void) {
    TEST_ASSERT_EQUAL_INT(25, sum_odd_numbers(10));  // 1+3+5+7+9=25
    TEST_ASSERT_EQUAL_INT(9, sum_odd_numbers(5));    // 1+3+5=9
    TEST_ASSERT_EQUAL_INT(1, sum_odd_numbers(1));
}

void test_count_non_zero(void) {
    int arr1[] = {1, 0, 2, 0, 3};
    TEST_ASSERT_EQUAL_INT(3, count_non_zero(arr1, 5));
    
    int arr2[] = {0, 0, 0};
    TEST_ASSERT_EQUAL_INT(0, count_non_zero(arr2, 3));
}

void test_sum_positive(void) {
    int arr[] = {1, -2, 3, -4, 5};
    TEST_ASSERT_EQUAL_INT(9, sum_positive(arr, 5));
}

void test_sum_skip_multiples_of_3(void) {
    // 1到10：1+2+4+5+7+8+10 = 37
    // (总和55 - 3+6+9=18 = 37)
    TEST_ASSERT_EQUAL_INT(37, sum_skip_multiples_of_3(10));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sum_odd_numbers);
    RUN_TEST(test_count_non_zero);
    RUN_TEST(test_sum_positive);
    RUN_TEST(test_sum_skip_multiples_of_3);
    return UNITY_END();
}
