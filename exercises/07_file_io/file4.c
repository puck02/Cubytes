#include "unity.h"
#include <stdio.h>
#include <string.h>

int count_lines(const char *filename) {
    // TODO: 实现这个函数
    
}
    
    int count = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }
    
    fclose(file);
    return count;
}

int copy_file(const char *src, const char *dest) {
    // TODO: 实现这个函数
    
}
    
    FILE *dest_file = fopen(dest, "w");
    if (dest_file == NULL) {
        fclose(src_file);
        return 0;
    }
    
    int ch;
    while ((ch = fgetc(src_file)) != EOF) {
        if (ferror(src_file)) {
            clearerr(src_file);
            fclose(src_file);
            fclose(dest_file);
            return 0;
        }
        fputc(ch, dest_file);
    }
    
    fclose(src_file);
    fclose(dest_file);
    return 1;
}

void setUp(void) {}
void tearDown(void) {}

void test_count_lines(void) {
    const char *filename = "test_file4.txt";
    
    // 创建测试文件
    FILE *file = fopen(filename, "w");
    fprintf(file, "line1\n");
    fprintf(file, "line2\n");
    fprintf(file, "line3\n");
    fclose(file);
    
    // 统计行数
    int lines = count_lines(filename);
    TEST_ASSERT_EQUAL_INT(3, lines);
    
    remove(filename);
}

void test_copy_file(void) {
    const char *src = "test_src.txt";
    const char *dest = "test_dest.txt";
    
    // 创建源文件
    FILE *file = fopen(src, "w");
    fprintf(file, "Hello, World!");
    fclose(file);
    
    // 复制文件
    int result = copy_file(src, dest);
    TEST_ASSERT_EQUAL_INT(1, result);
    
    // 验证内容
    char buffer[100];
    file = fopen(dest, "r");
    fgets(buffer, 100, file);
    fclose(file);
    TEST_ASSERT_EQUAL_STRING("Hello, World!", buffer);
    
    remove(src);
    remove(dest);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_count_lines);
    RUN_TEST(test_copy_file);
    return UNITY_END();
}
