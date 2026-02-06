<div align="center">

<img src="icon.png" alt="Cling Logo" width="200"/>

# 🎯 Cling - C语言快速入门练习系统

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C Standard](https://img.shields.io/badge/C-C11-brightgreen.svg)]()

</div>

## 📖 简介

Cling是一个交互式C语言学习系统，包含58道精心设计的练习，帮助初学者快速掌握C语言基础知识。通过实时反馈的watch模式和测试驱动的学习方式，让C语言学习更加高效有趣。

### ✨ 特性

- 🎓 **渐进式学习路径** - 8个主题章节，从零基础到项目实战
- ⚡ **实时反馈** - Watch模式自动检测文件变化并运行测试
- ✅ **测试驱动** - 每道题配有单元测试，明确的通过标准
- 💡 **分级提示系统** - 2-3级渐进式提示，帮助而不透露答案
- 🎮 **最终项目** - 链表实现的终端贪吃蛇游戏
- 🌈 **美观输出** - 彩色终端反馈，清晰易读
- 📊 **进度跟踪** - 自动保存学习进度

## 📚 学习路径

| 章节 | 题目数 | 主题 | 验证方式 |
|-----|-------|------|---------|
| 00 | 2 | Introduction - 编译基础 | 编译验证 |
| 01 | 8 | Variables & Types - 变量与类型 | 混合 |
| 02 | 8 | Control Flow - 控制流 | 单元测试 |
| 03 | 8 | Functions - 函数 | 单元测试 |
| 04 | 8 | Arrays & Strings - 数组与字符串 | 单元测试 |
| 05 | 11 | Pointers - 指针（重点） | 单元测试 |
| 06 | 8 | Structs & Memory - 结构体与内存 | 单元测试 |
| 07 | 4 | File I/O - 文件操作 | 单元测试 |
| 08 | 1 | Final Project - 贪吃蛇游戏 | 综合测试 |

**总计：58道练习 + 1个综合项目**

## 🚀 快速开始

### ⚡ 一键安装（推荐）

自动安装Cling + C编译器 + CMake，开箱即用！

**macOS / Linux：**
```bash
curl -fsSL https://raw.githubusercontent.com/puck02/Cling/main/scripts/install.sh | bash
```

**Windows（以管理员身份运行PowerShell）：**
```powershell
iwr -useb https://raw.githubusercontent.com/puck02/Cling/main/scripts/install.ps1 | iex
```

安装完成后，克隆仓库开始学习：
```bash
git clone https://github.com/puck02/Cling.git
cd Cling
cling watch
```

---

<details>
<summary>📦 手动安装（如果一键安装失败）</summary>

### 1. 安装Cling工具

前往 [Releases页面](https://github.com/puck02/Cling/releases) 下载最新版本：

**Windows：**
- 下载 `cling-windows-x86_64.exe`
- 重命名为 `cling.exe`，放到任意文件夹
- 双击运行，或在CMD中使用

**macOS：**
```bash
# Intel芯片下载 cling-macos-x86_64
# M1/M2芯片下载 cling-macos-aarch64

# 添加执行权限
chmod +x ~/Downloads/cling-macos-*

# 移动到系统路径（可选）
sudo mv ~/Downloads/cling-macos-* /usr/local/bin/cling
```

### 2. 安装C编译器和CMake

Cling需要C编译器来编译你的练习代码。

**macOS：**
```bash
# 安装Xcode Command Line Tools
xcode-select --install

# 安装CMake
brew install cmake
# 如果没有Homebrew：/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

**Windows：**
```powershell
# 在PowerShell（管理员模式）中运行
# 安装Chocolatey包管理器
Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

# 安装MinGW和CMake
choco install mingw cmake -y

# 验证安装
gcc --version
cmake --version
```

<details>
<summary>💡 Windows手动安装（如果上面的命令失败）</summary>

**安装MinGW-w64：**
1. 下载：https://github.com/niXman/mingw-builds-binaries/releases
2. 选择 `x86_64-*-release-win32-seh-ucrt-*.7z`
3. 解压到 `C:\mingw64`
4. 添加环境变量：右键"此电脑" → 属性 → 高级系统设置 → 环境变量 → 编辑Path → 添加 `C:\mingw64\bin`

**安装CMake：**
1. 下载：https://cmake.org/download/
2. 运行安装器，勾选"Add CMake to system PATH"

</details>

### 3. 克隆仓库并开始学习

```bash
# 克隆练习仓库
git clone https://github.com/puck02/Cling.git
cd Cling

# 启动watch模式开始学习
cling watch
```

</details>

> 💡 **完全新手？** 不用担心！watch模式会自动检测你的代码更改并给出即时反馈，跟着提示一步步来就好。

## 🎮 使用指南

### 命令参考

> ⚠️ **注意：** 所有命令需要在项目根目录（Cling文件夹）下运行。

| 命令 | 说明 | 示例 |
|------|------|------|
| `cling` / `cling watch` | 启动watch模式，自动检测文件变化 | `cling watch` |
| `cling run <name>` | 运行指定练习 | `cling run variables1` |
| `cling list` | 列出所有练习和完成状态 | `cling list` |
| `cling reset <name>` | 重置练习到初始状态 | `cling reset loops2` |
| `cling check` | 检查当前练习是否通过 | `cling check` |
| `cling check-all` | 检查所有练习的完成情况 | `cling check-all` |

## 💻 练习结构

### 编译验证练习（前10题）

重点在于修复语法错误，让代码能够编译通过：

```c
// exercises/00_intro/intro1.c
#include <stdio.h>

int main(void) {
    // TODO: 修复下面的语法错误
    printf("Hello, World!")
    return 0;
}
```

### 测试驱动练习（后40题）

需要实现函数逻辑，通过所有单元测试：

```c
// exercises/03_functions/functions1.c
#include "unity.h"

int add(int a, int b) {
    // TODO: 实现加法函数
    return 0;
}

void test_add(void) {
    TEST_ASSERT_EQUAL_INT(5, add(2, 3));
    TEST_ASSERT_EQUAL_INT(0, add(-1, 1));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add);
    return UNITY_END();
}
```

## 🐍 最终项目：贪吃蛇

完成所有练习后，挑战终端贪吃蛇游戏项目！

**你将实现：**
- 🔗 链表操作（节点创建、插入、删除）
- 🎯 碰撞检测逻辑
- 🍎 食物生成算法
- 🎮 游戏状态更新
- 💾 内存管理（防止泄漏）

**框架已提供：**
- 🖥️ 终端UI渲染（ANSI颜色、动画）
- ⌨️ 键盘输入处理
- ⏱️ 游戏主循环和计时
- 📦 完整数据结构定义

## 🛠️ 技术细节

### 构建系统

使用CMake管理多文件项目：

```bash
# 编译所有练习
mkdir build && cd build
cmake ..
make

# 运行特定练习
./exercises/01_variables/variables1
```

### 测试框架

使用Unity测试框架进行单元测试：

```c
#include "unity.h"

void setUp(void) {
    // 每个测试前执行
}

void tearDown(void) {
    // 每个测试后执行
}

void test_function(void) {
    TEST_ASSERT_EQUAL_INT(expected, actual);
}
```

### 编译选项

所有代码使用C11标准和严格编译选项：

```bash
gcc -Wall -Wextra -Werror -std=c11 -O2
```

## 📖 学习建议

1. **按顺序完成** - 练习难度递进，跳过会导致困难
2. **先思考再看提示** - 独立思考能加深理解
3. **理解测试用例** - 测试用例展示了函数的预期行为
4. **查阅文档** - 遇到不熟悉的函数，查阅[cppreference](https://en.cppreference.com/w/c)
5. **动手实践** - 修改测试用例，尝试不同输入
6. **查看解答** - 完成后查看solutions/目录的标准答案

## 🤝 贡献

欢迎贡献练习题目、修复bug或改进文档！

详见 [CONTRIBUTING.md](CONTRIBUTING.md)

## 📜 许可证

MIT License - 详见 [LICENSE](LICENSE)

## 🙏 致谢

- 灵感来自 [Rustlings](https://github.com/rust-lang/rustlings)
- 测试框架 [Unity](https://github.com/ThrowTheSwitch/Unity)

## 📞 联系方式

- 问题反馈：[GitHub Issues](https://github.com/yourusername/cling/issues)
- 讨论交流：[GitHub Discussions](https://github.com/yourusername/cling/discussions)

---

<div align="center">

**开始你的C语言学习之旅！** 🚀

`cling watch`

</div>
