#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// ============================================================================
// 游戏初始化
// ============================================================================
// 创建游戏实例，初始化蛇和食物
// 参数：width - 游戏区域宽度，height - 游戏区域高度
// 返回：初始化好的游戏指针
Game* game_init(int width, int height) {
    // 分配游戏结构体内存
    Game *game = (Game*)malloc(sizeof(Game));
    game->width = width;
    game->height = height;
    game->score = 0;
    game->state = GAME_RUNNING;
    
    // 初始化蛇结构体
    game->snake = (Snake*)malloc(sizeof(Snake));
    game->snake->head = NULL;
    game->snake->tail = NULL;
    game->snake->direction = DIR_RIGHT;  // 初始向右移动
    game->snake->length = 0;
    
    // 创建初始蛇身（3节，从游戏区域中间开始）
    // 注意：蛇是从右向左构建的（右边是头）
    snake_insert_head(game->snake, width/2, height/2);
    snake_insert_head(game->snake, width/2 + 1, height/2);
    snake_insert_head(game->snake, width/2 + 2, height/2);
    
    // 生成第一个食物
    game->food.active = false;
    food_generate(&game->food, game->snake, width, height);
    
    return game;
}

// ============================================================================
// 终端控制函数
// ============================================================================

// 清屏（初始化时使用）
// ANSI转义序列：\033[2J 清空屏幕内容，\033[H 移动光标到左上角(1,1)
void clear_screen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

// 移动光标到起始位置（刷新时使用）
// 只移动光标，不清屏 - 这是避免闪烁的关键！
void reset_cursor(void) {
    printf("\033[H");
    fflush(stdout);
}

// 隐藏/显示光标
// \033[?25l 隐藏光标（游戏中使用，让画面更干净）
// \033[?25h 显示光标（游戏结束时恢复）
void set_cursor_visible(bool visible) {
    if (visible) {
        printf("\033[?25h");
    } else {
        printf("\033[?25l");
    }
    fflush(stdout);
}

// ============================================================================
// 游戏渲染
// ============================================================================
// 在终端中绘制游戏画面
// 关键优化：第一次渲染清屏，后续只移动光标（避免闪烁）
void game_render(Game *game) {
    static bool first_render = true;  // 静态变量，跨函数调用保持值
    
    // 优化技巧：只在第一帧清屏，后续帧复用屏幕内容
    if (first_render) {
        clear_screen();              // 清空屏幕
        set_cursor_visible(false);   // 隐藏闪烁的光标
        first_render = false;
    } else {
        reset_cursor();              // 只移动光标，不清屏
    }
    
    // 绘制上边框（使用Unicode字符，比ASCII美观）
    printf("┌");
    for (int i = 0; i < game->width; i++) printf("─");
    printf("┐\n");
    
    // 遍历游戏区域的每一个位置
    for (int y = 0; y < game->height; y++) {
        printf("│");  // 左边框
        for (int x = 0; x < game->width; x++) {
            bool is_snake = false;
            bool is_head = false;
            
            // 遍历蛇身，检查当前位置是否有蛇
            SnakeNode *current = game->snake->head;
            while (current) {
                if (current->pos.x == x && current->pos.y == y) {
                    is_snake = true;
                    if (current == game->snake->head) is_head = true;
                    break;
                }
                current = current->next;
            }
            
            // 检查当前位置是否是食物
            bool is_food = game->food.active && 
                          game->food.pos.x == x && 
                          game->food.pos.y == y;
            
            // 根据位置内容渲染不同字符
            if (is_head) {
                printf("@");  // 蛇头
            } else if (is_snake) {
                printf("o");  // 蛇身
            } else if (is_food) {
                printf("*");  // 食物
            } else {
                printf(" ");  // 空位
            }
        }
        printf("│\n");  // 右边框
    }
    
    // 绘制下边框
    printf("└");
    for (int i = 0; i < game->width; i++) printf("─");
    printf("┘\n");
    
    // 显示游戏信息（额外空格确保覆盖之前更长的内容）
    printf("分数: %d | 长度: %d         \n", game->score, game->snake->length);
   ============================================================================
// 终端模式控制
// ============================================================================
// 设置终端为非阻塞模式，使游戏可以在不等待输入的情况下持续运行
// termios - Unix终端控制结构，fcntl - 文件控制函数
void set_nonblocking_mode(bool enable) {
    static struct termios old_term, new_term;  // 终端配置
    static int old_flags;                      // 文件标志
    
    if (enable) {
        // 保存当前终端设置（以便后续恢复）
        tcgetattr(STDIN_FILENO, &old_term);
        new_term = old_term;
        
        // 关闭两个标志：
        // ICANON - 标准输入模式（不需要回车就能读取）
        // ECHO - 回显（不在屏幕上显示输入的字符）
        new_term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
        
        // 设置标准输入为非阻塞模式（read不会等待）
        old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);
    } else {
   ============================================================================
// 输入处理
// ============================================================================
// 读取键盘输入并更新蛇的方向
// 支持方向键（ESC序列）和WASD，Q键退出
// 非阻塞：如果没有输入，立即返回而不等待
void game_handle_input(Game *game) {
    char c;
    // read返回读取的字节数，0表示没有输入，-1表示错误
    if (read(STDIN_FILENO, &c, 1) > 0) {
        Direction new_dir = game->snake->direction;
        
        // 方向键是ESC序列：ESC [ A/B/C/D
        if (c == 27) {  // ESC字符 (ASCII 27)
            char seq[2];
            // 读取后续的两个字符 '[' 和方向字符
            if (read(STDIN_FILENO, &seq[0], 1) > 0 && 
                read(STDIN_FILENO, &seq[1], 1) > 0) {
                if (seq[0] == '[') {
                    switch (seq[1]) {
                        case 'A': new_dir = DIR_UP; break;     // ↑
                        case 'B': new_dir = DIR_DOWN; break;   // ↓
                        case 'D': new_dir = DIR_LEFT; break;   // ←
                        case 'C': new_dir = DIR_RIGHT; break;  // →
                    }
                }
            }
        } 
        // Q键退出
        else if (c == 'q' || c == 'Q') {
            game->state = GAME_QUIT;
            return;
        } 
        // WASD控制
        else if (c == 'w' || c == 'W') {
            new_dir = DIR_UP;
        } else if (c == 's' || c == 'S') {
            new_dir = DIR_DOWN;
        } else if (c == 'a' || c == 'A') {
            new_dir = DIR_LEFT;
        } else if (c == 'd' || c == 'D') {
            new_dir = DIR_RIGHT;
   ============================================================================
// 游戏主循环
// ============================================================================
// 游戏的核心循环：渲染 → 处理输入 → 更新状态 → 延迟
// 这是游戏引擎的标准结构（Game Loop Pattern）
void game_loop(Game *game) {
    set_nonblocking_mode(true);  // 启用非阻塞输入
    
    // 主循环：持续运行直到游戏结束
    while (game->state == GAME_RUNNING) {
        game_render(game);         // 1. 渲染当前画面
        game_handle_input(game);   // 2. 处理用户输入
        game_update(game);         // 3. 更新游戏逻辑（蛇移动、碰撞检测等）
        
        usleep(150000);  // 4. 延迟150ms（控制游戏速度，约6.7帧/秒）
    }
    
    // 游戏结束，恢复终端状态
    set_nonblocking_mode(false);   // 恢复阻塞模式
    set_cursor_visible(true);      // 显示光标
    
    // 显示结束画面
    printf("\n");
    if (game->state == GAME_OVER) {
        printf("💀 游戏结束！最终分数: %d\n", game->score);
    } else {
        printf("👋 游戏退出\n");
    }
}

// ============================================================================
// 资源释放
// ============================================================================
// 释放游戏占用的所有内存（防止内存泄漏）
void game_free(Game *game) {
    if (game) {
        if (game->snake) {
            snake_free(game->snake);  // 释放蛇的所有节点
            free(game->snake);         // 释放蛇结构体
        }
        free(game);  // 释放游戏结构体
    }
}

// ============================================================================
// 主函数
// ============================================================================
// 程序入口：初始化 → 运行 → 清理
int main(void) {
    printf("🐍 贪吃蛇游戏 🐍\n");
    printf("即将开始...\n");
    sleep(1);  // 等待1秒
    
    Game *game = game_init(30, 15);  // 创建30x15的游戏区域
    game_loop(game);                  // 运行游戏主循环
    game_free(game);                  // 释放资源戏退出\n");
    }
}

// 释放游戏资源
void game_free(Game *game) {
    if (game) {
        if (game->snake) {
            snake_free(game->snake);
            free(game->snake);
        }
        free(game);
    }
}

// 主函数
int main(void) {
    printf("🐍 贪吃蛇游戏 🐍\n");
    printf("即将开始...\n");
    sleep(1);
    
    Game *game = game_init(30, 15);
    game_loop(game);
    game_free(game);
    
    return 0;
}
