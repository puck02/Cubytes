#include "unity.h"
#include <stdio.h>

int write_student_data(const char *filename, const char *name, int age, double score) {
    // TODO: 实现这个函数
    
}
    fprintf(file, "%s\n", name);
    fprintf(file, "%d\n", age);
    fprintf(file, "%.2f\n", score);
    fclose(file);
    return 1;
}

int read_student_data(const char *filename, char *name, int *age, double *score) {
    // TODO: 实现这个函数
    
}
    if (fscanf(file, "%s", name) != 1) {
        fclose(file);
        return 0;
    }
    if (fscanf(file, "%d", age) != 1) {
        fclose(file);
        return 0;
    }
    if (fscanf(file, "%lf", score) != 1) {
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

void setUp(void) {}
void tearDown(void) {}

void test_write_and_read_formatted(void) {
    const char *filename = "test_file2.txt";
    
    int write_result = write_student_data(filename, "Alice", 20, 85.5);
    TEST_ASSERT_EQUAL_INT(1, write_result);
    
    char name[50];
    int age;
    double score;
    int read_result = read_student_data(filename, name, &age, &score);
    TEST_ASSERT_EQUAL_INT(1, read_result);
    TEST_ASSERT_EQUAL_STRING("Alice", name);
    TEST_ASSERT_EQUAL_INT(20, age);
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 85.5, score);
    
    remove(filename);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_write_and_read_formatted);
    return UNITY_END();
}
