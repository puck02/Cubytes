#include "unity.h"
#include <stdlib.h>
#include <string.h>

// 学习目标：实现完整的动态数据结构
// 练习结构体、动态内存和自动扩容

// 动态字符串结构
typedef struct {
    char *data;      // 存储字符的缓冲区
    int size;        // 当前已使用的字符数
    int capacity;    // 缓冲区总容量
} DynamicString;

DynamicString* create_dynamic_string(void) {
    DynamicString *ds = (DynamicString *)malloc(sizeof(DynamicString));
    ds->capacity = 8;
    ds->size = 0;
    ds->data = (char *)malloc(ds->capacity);
    return ds;
}

void append_char(DynamicString *ds, char c) {
    // TODO: 实现这个函数
    
}
    ds->data[ds->size++] = c;
}

void free_dynamic_string(DynamicString *ds) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_create_dynamic_string(void) {
    DynamicString *ds = create_dynamic_string();
    TEST_ASSERT_NOT_NULL(ds);
    TEST_ASSERT_NOT_NULL(ds->data);
    TEST_ASSERT_EQUAL_INT(0, ds->size);
    TEST_ASSERT_EQUAL_INT(8, ds->capacity);
    free_dynamic_string(ds);
}

void test_append_char(void) {
    DynamicString *ds = create_dynamic_string();
    
    append_char(ds, 'h');
    append_char(ds, 'e');
    append_char(ds, 'l');
    append_char(ds, 'l');
    append_char(ds, 'o');
    
    TEST_ASSERT_EQUAL_INT(5, ds->size);
    TEST_ASSERT_EQUAL_CHAR('h', ds->data[0]);
    TEST_ASSERT_EQUAL_CHAR('o', ds->data[4]);
    
    free_dynamic_string(ds);
}

void test_auto_expand(void) {
    DynamicString *ds = create_dynamic_string();
    
    // 添加超过初始容量的字符，测试自动扩容
    for (int i = 0; i < 20; i++) {
        append_char(ds, 'a');
    }
    
    TEST_ASSERT_EQUAL_INT(20, ds->size);
    TEST_ASSERT_TRUE(ds->capacity >= 20);
    
    free_dynamic_string(ds);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_dynamic_string);
    RUN_TEST(test_append_char);
    RUN_TEST(test_auto_expand);
    return UNITY_END();
}
