#include "unity.h"
#include <string.h>

typedef struct {
    char name[50];
    int age;
    double score;
} Student;

Student create_student(const char *name, int age, double score) {
    Student s;
    strcpy(s.name, name);
    s.age = age;
    s.score = score;
    return s;
}

int is_passing(Student *s) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_create_student(void) {
    Student s = create_student("Alice", 20, 85.5);
    TEST_ASSERT_EQUAL_STRING("Alice", s.name);
    TEST_ASSERT_EQUAL_INT(20, s.age);
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 85.5, s.score);
}

void test_is_passing(void) {
    Student s1 = create_student("Bob", 19, 75.0);
    Student s2 = create_student("Charlie", 21, 55.0);
    TEST_ASSERT_TRUE(is_passing(&s1));
    TEST_ASSERT_FALSE(is_passing(&s2));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_student);
    RUN_TEST(test_is_passing);
    return UNITY_END();
}
