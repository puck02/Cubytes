#include "snake.h"
#include <stdlib.h>
#include <string.h>

// ============================================================================
// 练习 1: 创建链表节点
// ============================================================================
// 功能：分配一个新的蛇节点，并初始化其位置
// 提示：使用 malloc 分配内存，记得检查返回值
SnakeNode* snake_node_create(int x, int y) {
    // TODO: 分配 SnakeNode 内存
    SnakeNode *node = NULL;  // 你的代码：node = (SnakeNode*)malloc(sizeof(SnakeNode));
    if (node == NULL) {
        return NULL;
    }
    node->pos.x = x;
    node->pos.y = y;
    node->next = NULL;
    return node;
}

// ============================================================================
// 练习 2: 在链表头部插入节点
// ============================================================================
// 功能：在蛇头部添加新节点（蛇移动时使用）
// 提示：新节点的 next 应该指向当前的 head
void snake_insert_head(Snake *snake, int x, int y) {
    if (snake == NULL) {
        return;
    }
    
    SnakeNode *new_head = snake_node_create(x, y);
    if (new_head == NULL) {
        return;
    }
    
    // TODO: 将新节点链接到链表头部
    new_head->next = NULL;  // 你的代码：new_head->next = snake->head;
    snake->head = new_head;
    
    if (snake->tail == NULL) {
        snake->tail = new_head;
    }
    
    snake->length++;
}

// ============================================================================
// 练习 3: 删除链表尾部节点
// ============================================================================
// 功能：删除蛇尾（蛇移动且没吃食物时使用）
// 提示：需要找到倒数第二个节点，条件是 current->next != snake->tail
void snake_remove_tail(Snake *snake) {
    if (snake == NULL || snake->head == NULL) {
        return;
    }
    
    if (snake->head == snake->tail) {
        free(snake->head);
        snake->head = NULL;
        snake->tail = NULL;
        snake->length = 0;
        return;
    }
    
    SnakeNode *current = snake->head;
    // TODO: 找到倒数第二个节点
    while (current != NULL) {  // 你的代码：while (current->next != snake->tail)
        current = current->next;
    }
    
    free(snake->tail);
    snake->tail = current;
    current->next = NULL;
    snake->length--;
}

// ============================================================================
// 碰撞检测（完整实现）
// ============================================================================
// 检查蛇头是否撞墙或咬到自己
bool snake_check_collision(Snake *snake, int width, int height) {
    if (snake == NULL || snake->head == NULL) {
        return false;
    }
    
    Position head_pos = snake->head->pos;
    
    // 检查撞墙
    if (head_pos.x < 0 || head_pos.x >= width || 
        head_pos.y < 0 || head_pos.y >= height) {
        return true;
    }
    
    // 检查自咬（从第二节开始检查）
    SnakeNode *current = snake->head->next;
    while (current != NULL) {
        if (current->pos.x == head_pos.x && current->pos.y == head_pos.y) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

// ============================================================================
// 蛇的移动（完整实现）
// ============================================================================
// 根据方向在头部插入新节点
void snake_move(Snake *snake, Direction dir) {
    if (snake == NULL || snake->head == NULL) {
        return;
    }
    
    Position head_pos = snake->head->pos;
    int new_x = head_pos.x;
    int new_y = head_pos.y;
    
    switch (dir) {
        case DIR_UP:    new_y--; break;
        case DIR_DOWN:  new_y++; break;
        case DIR_LEFT:  new_x--; break;
        case DIR_RIGHT: new_x++; break;
    }
    
    snake_insert_head(snake, new_x, new_y);
}

// ============================================================================
// 练习 4: 生成食物
// ============================================================================
// 功能：在随机位置生成食物（不能与蛇身重合）
// 提示：使用 rand() % width 生成 0 到 width-1 的随机数
void food_generate(Food *food, Snake *snake, int width, int height) {
    if (food == NULL || snake == NULL) {
        return;
    }
    
    bool valid = false;
    while (!valid) {
        // TODO: 生成随机坐标
        food->pos.x = 0;  // 你的代码：food->pos.x = rand() % width;
        food->pos.y = 0;  // 你的代码：food->pos.y = rand() % height;
        
        // 检查是否与蛇身重合
        valid = true;
        SnakeNode *current = snake->head;
        while (current != NULL) {
            if (current->pos.x == food->pos.x && current->pos.y == food->pos.y) {
                valid = false;
                break;
            }
            current = current->next;
        }
    }
    
    food->active = true;
}

// ============================================================================
// 游戏状态更新（完整实现）
// ============================================================================
// 每一帧调用：移动蛇、检测碰撞、检测食物、更新分数
void game_update(Game *game) {
    if (game == NULL || game->state != GAME_RUNNING) {
        return;
    }
    
    Snake *snake = game->snake;
    bool ate_food = false;
    
    // 1. 移动蛇
    snake_move(snake, snake->direction);
    
    // 2. 检查碰撞
    if (snake_check_collision(snake, game->width, game->height)) {
        game->state = GAME_OVER;
        return;
    }
    
    // 3. 检查是否吃到食物
    if (game->food.active && 
        snake->head->pos.x == game->food.pos.x && 
        snake->head->pos.y == game->food.pos.y) {
        game->score += 10;
        game->food.active = false;
        ate_food = true;
        food_generate(&game->food, snake, game->width, game->height);
    }
    
    // 4. 如果没吃到食物，删除尾部（蛇不变长）
    if (!ate_food) {
        snake_remove_tail(snake);
    }
}

// ============================================================================
// 释放蛇的内存（完整实现）
// ============================================================================
// 遍历链表，释放所有节点
void snake_free(Snake *snake) {
    if (snake == NULL) {
        return;
    }
    
    SnakeNode *current = snake->head;
    while (current != NULL) {
        SnakeNode *next = current->next;
        free(current);
        current = next;
    }
    
    // 注意：不释放 Snake 结构本身，由调用者负责
}

