#include "unity.h"
#include <stdlib.h>
#include <string.h>

// 学习目标：使用 realloc 调整已分配内存的大小
// realloc 可以增大或缩小已分配的内存块

int* resize_array(int *arr, int old_size, int new_size) {
    (void)old_size;  // 标记未使用的参数，避免警告
    return (int *)realloc(arr, new_size * sizeof(int));
}

char* resize_string(char *str, int new_size) {
    return (char *)realloc(str, new_size * sizeof(char));
}

void setUp(void) {}
void tearDown(void) {}

void test_resize_array(void) {
    int *arr = (int *)malloc(3 * sizeof(int));
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    
    arr = resize_array(arr, 3, 5);
    TEST_ASSERT_NOT_NULL(arr);
    
    // 原有数据应该保留
    TEST_ASSERT_EQUAL_INT(1, arr[0]);
    TEST_ASSERT_EQUAL_INT(2, arr[1]);
    TEST_ASSERT_EQUAL_INT(3, arr[2]);
    
    // 可以使用新空间
    arr[3] = 4;
    arr[4] = 5;
    TEST_ASSERT_EQUAL_INT(4, arr[3]);
    TEST_ASSERT_EQUAL_INT(5, arr[4]);
    
    free(arr);
}

void test_resize_string(void) {
    char *str = (char *)malloc(5 * sizeof(char));
    strcpy(str, "test");
    
    str = resize_string(str, 10);
    TEST_ASSERT_NOT_NULL(str);
    
    // 原有数据应该保留
    TEST_ASSERT_EQUAL_STRING("test", str);
    
    // 可以使用新空间
    strcat(str, " data");
    TEST_ASSERT_EQUAL_STRING("test data", str);
    
    free(str);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_resize_array);
    RUN_TEST(test_resize_string);
    return UNITY_END();
}
