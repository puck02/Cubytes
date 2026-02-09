#include "unity.h"

// TODO: 实现函数，返回数组中的最大值
int find_max(int arr[], int size) {
    // TODO: 实现这个函数
    
}
    }
    return max;
}

void setUp(void) {}
void tearDown(void) {}

void test_find_max(void) {
    int arr1[] = {1, 5, 3, 9, 2};
    TEST_ASSERT_EQUAL_INT(9, find_max(arr1, 5));
    
    int arr2[] = {-5, -1, -10, -3};
    TEST_ASSERT_EQUAL_INT(-1, find_max(arr2, 4));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_find_max);
    return UNITY_END();
}
