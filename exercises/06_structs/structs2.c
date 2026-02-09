#include "unity.h"
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

Point create_point(int x, int y) {
    // TODO: 实现这个函数
    
};
    return p;
}

int manhattan_distance(Point *p1, Point *p2) {
    // TODO: 实现这个函数
    
}

void setUp(void) {}
void tearDown(void) {}

void test_create_point(void) {
    Point p = create_point(3, 4);
    TEST_ASSERT_EQUAL_INT(3, p.x);
    TEST_ASSERT_EQUAL_INT(4, p.y);
}

void test_manhattan_distance(void) {
    Point p1 = {0, 0};
    Point p2 = {3, 4};
    TEST_ASSERT_EQUAL_INT(7, manhattan_distance(&p1, &p2));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_point);
    RUN_TEST(test_manhattan_distance);
    return UNITY_END();
}
