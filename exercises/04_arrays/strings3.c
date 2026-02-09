#include "unity.h"
#include <string.h>

int strings_equal(const char *str1, const char *str2) {
    // TODO: 实现这个函数
    
}
        i++;
    }
    return str1[i] == str2[i];
}

int count_char(const char *str, char ch) {
    // TODO: 实现这个函数
    
}
    }
    return count;
}

void setUp(void) {}
void tearDown(void) {}

void test_strings_equal(void) {
    TEST_ASSERT_EQUAL_INT(1, strings_equal("hello", "hello"));
    TEST_ASSERT_EQUAL_INT(0, strings_equal("hello", "world"));
    TEST_ASSERT_EQUAL_INT(1, strings_equal("", ""));
}

void test_count_char(void) {
    TEST_ASSERT_EQUAL_INT(2, count_char("hello", 'l'));  // "hello"中'l'出现2次
    TEST_ASSERT_EQUAL_INT(0, count_char("hello", 'x'));
    TEST_ASSERT_EQUAL_INT(1, count_char("hello", 'h'));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_strings_equal);
    RUN_TEST(test_count_char);
    return UNITY_END();
}
