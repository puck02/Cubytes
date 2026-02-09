#include "unity.h"
#include <stdlib.h>
#include <string.h>

int* allocate_zero_array(int size) {
    return (int *)calloc(size, sizeof(int));
}

char* duplicate_string(const char *str) {
    char *new_str = (char *)malloc(strlen(str) + 1);
    strcpy(new_str, str);
    return new_str;
}

void setUp(void) {}
void tearDown(void) {}

void test_allocate_zero_array(void) {
    int *arr = allocate_zero_array(5);
    TEST_ASSERT_NOT_NULL(arr);
    
    // calloc应该初始化为0
    for (int i = 0; i < 5; i++) {
        TEST_ASSERT_EQUAL_INT(0, arr[i]);
    }
    
    free(arr);
}

void test_duplicate_string(void) {
    char *str = duplicate_string("hello");
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("hello", str);
    free(str);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_allocate_zero_array);
    RUN_TEST(test_duplicate_string);
    return UNITY_END();
}
