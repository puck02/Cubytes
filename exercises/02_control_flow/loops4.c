#include "unity.h"

// 学习目标：理解 do-while 循环的特点
// do-while 循环至少执行一次，然后检查条件

// TODO: 实现函数，使用do-while循环求和
// 从start加到end（包含end）
int sum_range(int start, int end) {
    // TODO: 实现这个函数
    
} while (i <= end);
    return sum;
}

// TODO: 模拟输入验证（使用计数器而非真实输入）
// 返回第几次尝试得到有效值
// valid_value: 期望的有效值
// attempts: 尝试次数数组
// size: 数组大小
int validate_input(int valid_value, int attempts[], int size) {
    // TODO: 实现这个函数
    
} while (i < size);
    return count;
}

// TODO: 实现函数，计算一个数的数字和
// 例如：sum_digits(123) = 1 + 2 + 3 = 6
// 使用do-while确保至少处理一次（包括0）
int sum_digits(int n) {
    // TODO: 实现这个函数
    
} while (n > 0);
    return sum;
}

void setUp(void) {}
void tearDown(void) {}

void test_sum_range(void) {
    TEST_ASSERT_EQUAL_INT(15, sum_range(1, 5));  // 1+2+3+4+5=15
    TEST_ASSERT_EQUAL_INT(39, sum_range(4, 9));  // 4+5+6+7+8+9=39
    TEST_ASSERT_EQUAL_INT(5, sum_range(5, 5));   // 5=5
}

void test_validate_input(void) {
    int attempts1[] = {1, 2, 3, 5};
    TEST_ASSERT_EQUAL_INT(4, validate_input(5, attempts1, 4));
    
    int attempts2[] = {10, 20};
    TEST_ASSERT_EQUAL_INT(1, validate_input(10, attempts2, 2));
}

void test_sum_digits(void) {
    TEST_ASSERT_EQUAL_INT(6, sum_digits(123));
    TEST_ASSERT_EQUAL_INT(10, sum_digits(1234));
    TEST_ASSERT_EQUAL_INT(1, sum_digits(1));
    TEST_ASSERT_EQUAL_INT(0, sum_digits(0));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sum_range);
    RUN_TEST(test_validate_input);
    RUN_TEST(test_sum_digits);
    return UNITY_END();
}
