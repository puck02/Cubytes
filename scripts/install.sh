#!/bin/bash
# Cling 一键安装脚本 (macOS/Linux)
# 使用方法: curl -fsSL https://raw.githubusercontent.com/puck02/Cling/main/scripts/install.sh | bash

set -e

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}"
echo "  _____ _ _             "
echo " / ____| (_)            "
echo "| |    | |_ _ __   __ _ "
echo "| |    | | | '_ \\ / _\` |"
echo "| |____| | | | | | (_| |"
echo " \\_____|_|_|_| |_|\\__, |"
echo "                   __/ |"
echo "                  |___/ "
echo -e "${NC}"
echo -e "${GREEN}Cling - C语言快速入门练习系统${NC}"
echo ""

# 检测系统
OS="unknown"
ARCH="unknown"

if [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macos"
    if [[ $(uname -m) == "arm64" ]]; then
        ARCH="aarch64"
    else
        ARCH="x86_64"
    fi
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="linux"
    ARCH="x86_64"
fi

echo -e "${BLUE}[1/4]${NC} 检测系统环境..."
echo "  系统: $OS, 架构: $ARCH"

# 检查并安装C编译器
echo -e "\n${BLUE}[2/4]${NC} 检查C编译器..."

install_xcode_tools() {
    if ! xcode-select -p &> /dev/null; then
        echo -e "${YELLOW}  未找到Xcode Command Line Tools，正在安装...${NC}"
        echo -e "${YELLOW}  请在弹出的对话框中点击'安装'${NC}"
        xcode-select --install
        
        # 等待安装完成
        echo -e "${YELLOW}  等待安装完成...${NC}"
        until xcode-select -p &> /dev/null; do
            sleep 5
        done
        echo -e "${GREEN}  ✓ Xcode Command Line Tools 安装完成${NC}"
    else
        echo -e "${GREEN}  ✓ 已安装 Xcode Command Line Tools${NC}"
    fi
}

install_gcc_linux() {
    if ! command -v gcc &> /dev/null; then
        echo -e "${YELLOW}  未找到GCC，正在安装...${NC}"
        if command -v apt-get &> /dev/null; then
            sudo apt-get update && sudo apt-get install -y build-essential
        elif command -v yum &> /dev/null; then
            sudo yum groupinstall -y "Development Tools"
        elif command -v pacman &> /dev/null; then
            sudo pacman -S --noconfirm base-devel
        else
            echo -e "${RED}  ✗ 无法自动安装GCC，请手动安装${NC}"
            exit 1
        fi
        echo -e "${GREEN}  ✓ GCC 安装完成${NC}"
    else
        echo -e "${GREEN}  ✓ 已安装 GCC $(gcc --version | head -1)${NC}"
    fi
}

if [[ "$OS" == "macos" ]]; then
    install_xcode_tools
elif [[ "$OS" == "linux" ]]; then
    install_gcc_linux
fi

# 检查并安装CMake
echo -e "\n${BLUE}[3/4]${NC} 检查CMake..."

install_cmake_macos() {
    if ! command -v cmake &> /dev/null; then
        echo -e "${YELLOW}  未找到CMake，正在安装...${NC}"
        if command -v brew &> /dev/null; then
            brew install cmake
        else
            echo -e "${YELLOW}  未找到Homebrew，先安装Homebrew...${NC}"
            /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
            # 添加到PATH
            if [[ $(uname -m) == "arm64" ]]; then
                eval "$(/opt/homebrew/bin/brew shellenv)"
            else
                eval "$(/usr/local/bin/brew shellenv)"
            fi
            brew install cmake
        fi
        echo -e "${GREEN}  ✓ CMake 安装完成${NC}"
    else
        echo -e "${GREEN}  ✓ 已安装 CMake $(cmake --version | head -1)${NC}"
    fi
}

install_cmake_linux() {
    if ! command -v cmake &> /dev/null; then
        echo -e "${YELLOW}  未找到CMake，正在安装...${NC}"
        if command -v apt-get &> /dev/null; then
            sudo apt-get install -y cmake
        elif command -v yum &> /dev/null; then
            sudo yum install -y cmake
        elif command -v pacman &> /dev/null; then
            sudo pacman -S --noconfirm cmake
        else
            echo -e "${RED}  ✗ 无法自动安装CMake，请手动安装${NC}"
            exit 1
        fi
        echo -e "${GREEN}  ✓ CMake 安装完成${NC}"
    else
        echo -e "${GREEN}  ✓ 已安装 CMake $(cmake --version | head -1)${NC}"
    fi
}

if [[ "$OS" == "macos" ]]; then
    install_cmake_macos
elif [[ "$OS" == "linux" ]]; then
    install_cmake_linux
fi

# 下载并安装Cling
echo -e "\n${BLUE}[4/4]${NC} 安装Cling..."

CLING_VERSION="v0.1.0"
INSTALL_DIR="/usr/local/bin"

if [[ "$OS" == "macos" ]]; then
    ASSET_NAME="cling-macos-${ARCH}"
else
    ASSET_NAME="cling-linux-x86_64"
fi

DOWNLOAD_URL="https://github.com/puck02/Cling/releases/download/${CLING_VERSION}/${ASSET_NAME}"

echo "  下载 ${ASSET_NAME}..."
curl -fsSL "$DOWNLOAD_URL" -o /tmp/cling

echo "  安装到 ${INSTALL_DIR}..."
sudo mv /tmp/cling "$INSTALL_DIR/cling"
sudo chmod +x "$INSTALL_DIR/cling"

echo -e "${GREEN}  ✓ Cling 安装完成${NC}"

# 验证安装
echo -e "\n${GREEN}========================================${NC}"
echo -e "${GREEN}✓ 安装完成！${NC}"
echo -e "${GREEN}========================================${NC}"
echo ""
echo "验证安装:"
echo "  gcc --version"
gcc --version | head -1
echo "  cmake --version"
cmake --version | head -1
echo "  cling --version (如果可用)"
cling --help 2>/dev/null | head -3 || echo "  cling 已安装到 $INSTALL_DIR"

echo ""
echo -e "${BLUE}开始学习:${NC}"
echo "  1. 克隆练习仓库:"
echo "     git clone https://github.com/puck02/Cling.git"
echo "     cd Cling"
echo ""
echo "  2. 启动学习:"
echo "     cling watch"
echo ""
echo -e "${YELLOW}祝你学习愉快！🎉${NC}"
