#include "unity.h"
#include <stdlib.h>

// TODO: 实现这个函数
// 分配一个int数组并初始化为0
// size: 数组大小
// 返回：指向新分配数组的指针
int** allocate_2d_array(int rows, int cols) {
    int **arr = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            arr[i][j] = 0;
        }
    }
    return arr;
}

// TODO: 实现这个函数
// 释放二维数组
void free_2d_array(int **arr, int rows) {
    // TODO: 实现这个函数
    
}
    free(arr);
}

void setUp(void) {}
void tearDown(void) {}

void test_allocate_and_free_2d_array(void) {
    int **arr = allocate_2d_array(3, 4);
    TEST_ASSERT_NOT_NULL(arr);
    
    // 设置和读取值
    arr[0][0] = 1;
    arr[2][3] = 99;
    TEST_ASSERT_EQUAL_INT(1, arr[0][0]);
    TEST_ASSERT_EQUAL_INT(99, arr[2][3]);
    
    free_2d_array(arr, 3);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_allocate_and_free_2d_array);
    return UNITY_END();
}
