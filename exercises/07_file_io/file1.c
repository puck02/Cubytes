#include "unity.h"
#include <stdio.h>
#include <string.h>

int write_to_file(const char *filename, const char *content) {
    // TODO: 实现这个函数
    
}
    fputs(content, file);
    fclose(file);
    return 1;
}

int read_from_file(const char *filename, char *buffer, int size) {
    // TODO: 实现这个函数
    
}
    if (fgets(buffer, size, file) == NULL) {
        fclose(file);
        return 0;
    }
    // 移除换行符
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    fclose(file);
    return 1;
}

void setUp(void) {}
void tearDown(void) {}

void test_write_and_read(void) {
    const char *filename = "test_file1.txt";
    const char *content = "Hello, File I/O!";
    
    // 写入文件
    int write_result = write_to_file(filename, content);
    TEST_ASSERT_EQUAL_INT(1, write_result);
    
    // 读取文件
    char buffer[100];
    int read_result = read_from_file(filename, buffer, 100);
    TEST_ASSERT_EQUAL_INT(1, read_result);
    TEST_ASSERT_EQUAL_STRING(content, buffer);
    
    // 清理
    remove(filename);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_write_and_read);
    return UNITY_END();
}
