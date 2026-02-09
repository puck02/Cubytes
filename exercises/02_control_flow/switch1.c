#include "unity.h"

typedef enum {
    MONDAY = 1,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
} DayOfWeek;

// TODO: 实现这个函数
// 如果是工作日(MONDAY-FRIDAY)返回1
// 如果是周末(SATURDAY-SUNDAY)返回0
// 提示：使用switch语句，不要忘记break
int is_weekday(DayOfWeek day) {
    // TODO: 实现这个函数
    
}
}

void setUp(void) {}
void tearDown(void) {}

void test_weekdays(void) {
    TEST_ASSERT_EQUAL_INT(1, is_weekday(MONDAY));
    TEST_ASSERT_EQUAL_INT(1, is_weekday(WEDNESDAY));
    TEST_ASSERT_EQUAL_INT(1, is_weekday(FRIDAY));
}

void test_weekend(void) {
    TEST_ASSERT_EQUAL_INT(0, is_weekday(SATURDAY));
    TEST_ASSERT_EQUAL_INT(0, is_weekday(SUNDAY));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_weekdays);
    RUN_TEST(test_weekend);
    return UNITY_END();
}
