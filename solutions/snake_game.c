#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// 初始化游戏
Game* game_init(int width, int height) {
    Game *game = (Game*)malloc(sizeof(Game));
    game->width = width;
    game->height = height;
    game->score = 0;
    game->state = GAME_RUNNING;
    
    // 初始化蛇
    game->snake = (Snake*)malloc(sizeof(Snake));
    game->snake->head = NULL;
    game->snake->tail = NULL;
    game->snake->direction = DIR_RIGHT;
    game->snake->length = 0;
    
    // 创建初始蛇身（3节）
    snake_insert_head(game->snake, width/2, height/2);
    snake_insert_head(game->snake, width/2 + 1, height/2);
    snake_insert_head(game->snake, width/2 + 2, height/2);
    
    // 生成食物
    game->food.active = false;
    food_generate(&game->food, game->snake, width, height);
    
    return game;
}

// 清屏（初始化时使用）
void clear_screen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

// 移动光标到起始位置（刷新时使用）
void reset_cursor(void) {
    printf("\033[H");
    fflush(stdout);
}

// 隐藏/显示光标
void set_cursor_visible(bool visible) {
    if (visible) {
        printf("\033[?25h");
    } else {
        printf("\033[?25l");
    }
    fflush(stdout);
}

// 渲染游戏
void game_render(Game *game) {
    static bool first_render = true;
    
    // 第一次渲染清屏并隐藏光标，后续只移动光标
    if (first_render) {
        clear_screen();
        set_cursor_visible(false);
        first_render = false;
    } else {
        reset_cursor();
    }
    
    // 绘制上边框
    printf("┌");
    for (int i = 0; i < game->width; i++) printf("─");
    printf("┐\n");
    
    // 绘制游戏区域
    for (int y = 0; y < game->height; y++) {
        printf("│");
        for (int x = 0; x < game->width; x++) {
            bool is_snake = false;
            bool is_head = false;
            
            // 检查是否是蛇
            SnakeNode *current = game->snake->head;
            while (current) {
                if (current->pos.x == x && current->pos.y == y) {
                    is_snake = true;
                    if (current == game->snake->head) is_head = true;
                    break;
                }
                current = current->next;
            }
            
            // 检查是否是食物
            bool is_food = game->food.active && 
                          game->food.pos.x == x && 
                          game->food.pos.y == y;
            
            if (is_head) {
                printf("@");
            } else if (is_snake) {
                printf("o");
            } else if (is_food) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("│\n");
    }
    
    // 绘制下边框
    printf("└");
    for (int i = 0; i < game->width; i++) printf("─");
    printf("┘\n");
    
    // 显示信息（额外空格确保覆盖旧内容）
    printf("分数: %d | 长度: %d         \n", game->score, game->snake->length);
    printf("方向键/WASD控制 | Q退出     \n");
    
    fflush(stdout);
}

// 设置终端为非阻塞模式
void set_nonblocking_mode(bool enable) {
    static struct termios old_term, new_term;
    static int old_flags;
    
    if (enable) {
        tcgetattr(STDIN_FILENO, &old_term);
        new_term = old_term;
        new_term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
        
        old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
        fcntl(STDIN_FILENO, F_SETFL, old_flags);
    }
}

// 处理输入
void game_handle_input(Game *game) {
    char c;
    if (read(STDIN_FILENO, &c, 1) > 0) {
        Direction new_dir = game->snake->direction;
        
        if (c == 27) {  // ESC sequence
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) > 0 && 
                read(STDIN_FILENO, &seq[1], 1) > 0) {
                if (seq[0] == '[') {
                    switch (seq[1]) {
                        case 'A': new_dir = DIR_UP; break;
                        case 'B': new_dir = DIR_DOWN; break;
                        case 'D': new_dir = DIR_LEFT; break;
                        case 'C': new_dir = DIR_RIGHT; break;
                    }
                }
            }
        } else if (c == 'q' || c == 'Q') {
            game->state = GAME_QUIT;
            return;
        } else if (c == 'w' || c == 'W') {
            new_dir = DIR_UP;
        } else if (c == 's' || c == 'S') {
            new_dir = DIR_DOWN;
        } else if (c == 'a' || c == 'A') {
            new_dir = DIR_LEFT;
        } else if (c == 'd' || c == 'D') {
            new_dir = DIR_RIGHT;
        }
        
        // 防止反向移动
        if ((new_dir == DIR_UP && game->snake->direction != DIR_DOWN) ||
            (new_dir == DIR_DOWN && game->snake->direction != DIR_UP) ||
            (new_dir == DIR_LEFT && game->snake->direction != DIR_RIGHT) ||
            (new_dir == DIR_RIGHT && game->snake->direction != DIR_LEFT)) {
            game->snake->direction = new_dir;
        }
    }
}

// 游戏主循环
void game_loop(Game *game) {
    set_nonblocking_mode(true);
    
    while (game->state == GAME_RUNNING) {
        game_render(game);
        game_handle_input(game);
        game_update(game);
        
        usleep(150000);  // 150ms延迟，流畅刷新
    }
    
    set_nonblocking_mode(false);
    set_cursor_visible(true);
    
    // 显示结束画面
    printf("\n");
    if (game->state == GAME_OVER) {
        printf("💀 游戏结束！最终分数: %d\n", game->score);
    } else {
        printf("👋 游戏退出\n");
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
