#include "unity.h"

int string_length(const char *str) {
    // TODO: 实现这个函数
    
}
    return len;
}

char first_char(const char *str) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_string_length(void) {
    TEST_ASSERT_EQUAL_INT(5, string_length("hello"));
    TEST_ASSERT_EQUAL_INT(0, string_length(""));
    TEST_ASSERT_EQUAL_INT(13, string_length("Hello, World!"));
}

void test_first_char(void) {
    TEST_ASSERT_EQUAL_CHAR('h', first_char("hello"));
    TEST_ASSERT_EQUAL_CHAR('H', first_char("Hello"));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_string_length);
    RUN_TEST(test_first_char);
    return UNITY_END();
}
