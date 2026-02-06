# Final Project: Snake Game 🐍

恭喜来到最终项目！本项目将带你完整实现一个贪吃蛇游戏，包含完整的教程和代码实现。

## 📚 项目概述

这是一个综合性项目，整合了前面所有章节的知识：
- **01_variables**: 游戏状态变量（分数、长度、宽高）
- **02_control_flow**: 游戏主循环、碰撞检测逻辑
- **03_functions**: 模块化设计（8个核心函数）
- **04_arrays**: 二维游戏区域遍历
- **05_pointers**: 链表节点操作、指针传递
- **06_structs**: 游戏数据结构设计
- **07_file_io**: （可选）保存最高分

## 🏗️ 架构设计

### 整体架构

```
┌─────────────────────────────────────────┐
│           snake_game.c (UI层)            │
│  - 游戏初始化                            │
│  - 终端渲染（ANSI转义序列）              │
│  - 输入处理（非阻塞IO）                  │
│  - 游戏主循环                            │
└───────────────┬─────────────────────────┘
                │ 调用
┌───────────────▼─────────────────────────┐
│        snake_logic.c (逻辑层)            │
│  - 蛇的移动逻辑                          │
│  - 碰撞检测                              │
│  - 食物生成                              │
│  - 游戏状态更新                          │
└───────────────┬─────────────────────────┘
                │ 使用
┌───────────────▼─────────────────────────┐
│           snake.h (数据层)               │
│  - 数据结构定义                          │
│  - 枚举类型（方向、游戏状态）            │
│  - 函数声明                              │
└─────────────────────────────────────────┘
```

### 核心数据结构

```c
// 位置坐标
typedef struct {
    int x, y;
} Position;

// 链表节点 - 蛇的一节身体
typedef struct SnakeNode {
    Position pos;
    struct SnakeNode *next;  // 指向下一节
} SnakeNode;

// 蛇 - 用链表表示
typedef struct {
    SnakeNode *head;    // 头指针（蛇头）
    SnakeNode *tail;    // 尾指针（蛇尾）
    Direction direction; // 移动方向
    int length;         // 长度
} Snake;

// 游戏状态
typedef struct {
    Snake *snake;
    Food food;
    int width, height;
    int score;
    GameState state;
} Game;
```

**为什么使用链表？**
- ✅ 动态长度：蛇吃食物后可以自然增长
- ✅ 高效插入删除：在头尾操作都是 O(1)
- ✅ 内存高效：只存储实际蛇身，不需要存储整个游戏区域

## 🎮 游戏逻辑详解

### 1. 蛇的移动机制

**核心思想**：移动 = 在头部插入新节点 + 删除尾部节点

```
初始状态:  tail → [o] → [o] → [@] ← head

移动一步（没吃食物）:
1. 在头部插入新节点
   tail → [o] → [o] → [@] → [@]新
   
2. 删除尾部节点
   [o]删 ← tail → [o] → [@] → [@]新 ← head
   
最终:   tail → [o] → [@] → [@] ← head
```

**吃到食物时**：只插入头部，不删除尾部 → 蛇变长了！

### 2. 碰撞检测

需要检测两种碰撞：

**撞墙**：
```c
if (head_pos.x < 0 || head_pos.x >= width || 
    head_pos.y < 0 || head_pos.y >= height) {
    // 游戏结束
}
```

**自咬**：遍历蛇身，检查头部是否与身体重合
```c
SnakeNode *current = snake->head->next;  // 从第二节开始
while (current != NULL) {
    if (头部位置 == current位置) {
        // 游戏结束
    }
    current = current->next;
}
```

### 3. 食物生成算法

```c
do {
    随机生成坐标 (x, y)
} while (坐标与蛇身重合);
```

使用 `rand()` 生成随机位置，确保不会生成在蛇身上。

### 4. 游戏更新流程

每一帧的更新顺序：
1. 🐍 移动蛇（根据当前方向）
2. 💥 检查碰撞（墙壁 + 自身）
3. 🍎 检查是否吃到食物
4. ➕ 如果吃到：加分 + 生成新食物
5. ✂️ 如果没吃到：删除尾节点

## 🖥️ 终端渲染技术

### ANSI 转义序列

在终端中实现流畅的游戏画面需要使用 ANSI 转义序列：

| 功能 | 转义序列 | 说明 |
|------|----------|------|
| 清屏 | `\033[2J\033[H` | 清空屏幕并移动光标到左上角 |
| 移动光标 | `\033[H` | 移动光标到左上角（不清屏）|
| 隐藏光标 | `\033[?25l` | 游戏中隐藏闪烁的光标 |
| 显示光标 | `\033[?25h` | 游戏结束后恢复光标 |

**优化技巧**：
- ✅ 第一帧：清屏 + 隐藏光标
- ✅ 后续帧：只移动光标（避免闪烁）
- ✅ 使用 Unicode 字符绘制边框：`┌ ─ ┐ │ └ ┘`

### 非阻塞输入

游戏需要在不等待用户输入的情况下持续运行：

```c
// 使用 termios 修改终端模式
struct termios new_term;
new_term.c_lflag &= ~(ICANON | ECHO);  // 关闭标准模式和回显

// 使用 fcntl 设置非阻塞
fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

// 读取输入（不会阻塞）
char c;
if (read(STDIN_FILENO, &c, 1) > 0) {
    // 处理按键
}
```

## 📝 你需要实现的部分

### 在 `snake_logic.c` 中（4个简单挖空）

大部分代码已经提供，你只需要完成以下简单部分：

1. **snake_node_create()** - 分配节点内存（3行代码）
2. **snake_insert_head()** - 更新头指针（2行代码）
3. **snake_remove_tail()** - 找到倒数第二个节点（1个循环条件）
4. **food_generate()** - 生成随机坐标（2行代码）

### 在 `snake_game.c` 中（已完整实现）

所有复杂的UI和输入处理代码都已提供，包括：
- ✅ ANSI 转义序列处理
- ✅ 非阻塞终端输入
- ✅ 流畅的游戏渲染
- ✅ 方向键和WASD控制
- ✅ 游戏主循环
- ✅ 游戏主循环

## 🚀 运行游戏

完成挖空部分后，编译并运行：

```bash
# 在 Cling 根目录下运行测试
cling check snake_test

# 编译游戏
cd build
make snake_game

# 运行游戏
./exercises/08_final_project/snake/snake_game
```

**操作说明：**
- ⬆️⬇️⬅️➡️ 方向键 或 WASD 控制方向
- Q 键退出游戏
- @ 是蛇头，o 是蛇身，* 是食物
- 吃到食物得10分，蛇身变长
- 撞墙或咬到自己游戏结束

## 💡 实现提示

### snake_node_create()
```c
// 1. 使用 malloc 分配内存
// 2. 检查是否分配成功
// 3. 初始化位置和next指针
```

### snake_insert_head()
```c
// 1. 创建新节点
// 2. 新节点的next指向当前head
// 3. 更新head指针
// 4. 如果是第一个节点，更新tail
```

### snake_remove_tail()
```c
// 关键：找到倒数第二个节点
SnakeNode *current = snake->head;
while (/* 什么条件？ */) {
    current = current->next;
}
```

### food_generate()
```c
// rand() % width  可以生成 0 到 width-1 的随机数
food->pos.x = ?;
food->pos.y = ?;
```

## 🎯 测试策略

1. **单元测试**：`cling check snake_test` 测试每个函数
2. **集成测试**：运行完整游戏，测试各种场景
   - 正常移动
   - 吃食物变长
   - 撞墙结束
   - 自咬结束
   - 边界情况（蛇填满屏幕）

## 🌟 扩展挑战（可选）

完成基础功能后，可以尝试：

1. **难度系统**：速度越来越快
2. **障碍物**：在地图上放置不能穿过的墙
3. **分数保存**：使用文件IO保存最高分
4. **彩色UI**：使用ANSI颜色代码
5. **音效**：使用系统beep（`\a`）
6. **双人模式**：两条蛇竞争

## 🏆 学习总结

通过这个项目，你应该掌握了：

✅ **数据结构**：链表的实际应用  
✅ **内存管理**：malloc/free的正确使用  
✅ **模块化设计**：分离逻辑层和UI层  
✅ **系统编程**：终端控制、非阻塞IO  
✅ **算法思维**：碰撞检测、随机生成  
✅ **调试技巧**：分层测试、边界情况  

## 📖 相关资源

- [ANSI 转义序列完整列表](https://en.wikipedia.org/wiki/ANSI_escape_code)
- [termios 文档](https://man7.org/linux/man-pages/man3/termios.3.html)
- [链表数据结构详解](https://en.wikipedia.org/wiki/Linked_list)

---

**恭喜完成所有练习！🎉**  
你已经掌握了C语言的核心知识，准备好迎接更大的挑战了！

