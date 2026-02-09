#include "unity.h"

// TODO: 实现这个函数
// 使用指针反转数组
// 提示：交换首尾元素，然后向中间移动
void reverse_array(int *arr, int size) {
    // TODO: 实现这个函数
    
}
}

// TODO: 实现这个函数
// 通过指针复制数组
void copy_array(int *dest, int *src, int size) {
    // TODO: 实现这个函数
    
}
}

void setUp(void) {}
void tearDown(void) {}

void test_reverse_array(void) {
    int arr[] = {1, 2, 3, 4, 5};
    reverse_array(arr, 5);
    TEST_ASSERT_EQUAL_INT(5, arr[0]);
    TEST_ASSERT_EQUAL_INT(4, arr[1]);
    TEST_ASSERT_EQUAL_INT(3, arr[2]);
    TEST_ASSERT_EQUAL_INT(2, arr[3]);
    TEST_ASSERT_EQUAL_INT(1, arr[4]);
}

void test_copy_array(void) {
    int src[] = {1, 2, 3, 4, 5};
    int dest[5];
    copy_array(dest, src, 5);
    for (int i = 0; i < 5; i++) {
        TEST_ASSERT_EQUAL_INT(src[i], dest[i]);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_reverse_array);
    RUN_TEST(test_copy_array);
    return UNITY_END();
}
