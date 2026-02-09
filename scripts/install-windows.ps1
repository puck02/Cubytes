# Cling 一键安装脚本 (Windows)
# 自动处理编码问题

# 设置控制台编码为 UTF-8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8
chcp 65001 > $null

Write-Host "==================================" -ForegroundColor Cyan
Write-Host "   Cling 安装程序 (Windows)" -ForegroundColor Green
Write-Host "==================================" -ForegroundColor Cyan
Write-Host ""

# 检查是否安装了 GCC
Write-Host "[1/4] 检查 GCC..." -ForegroundColor Yellow
$gccPath = Get-Command gcc -ErrorAction SilentlyContinue
if (-not $gccPath) {
    Write-Host "错误: 未找到 GCC 编译器" -ForegroundColor Red
    Write-Host "请先安装 MinGW-w64 或 MSYS2" -ForegroundColor Red
    Write-Host "下载地址: https://www.msys2.org/" -ForegroundColor Cyan
    exit 1
}
Write-Host "   已找到 GCC: $($gccPath.Source)" -ForegroundColor Green

# 检查是否安装了 Git
Write-Host "[2/4] 检查 Git..." -ForegroundColor Yellow
$gitPath = Get-Command git -ErrorAction SilentlyContinue
if (-not $gitPath) {
    Write-Host "错误: 未找到 Git" -ForegroundColor Red
    Write-Host "请先安装 Git: https://git-scm.com/" -ForegroundColor Cyan
    exit 1
}
Write-Host "   已找到 Git: $($gitPath.Source)" -ForegroundColor Green

# 克隆仓库
Write-Host "[3/4] 下载 Cling..." -ForegroundColor Yellow
if (Test-Path "Cling") {
    Write-Host "   目录已存在，跳过克隆" -ForegroundColor Yellow
} else {
    git clone https://github.com/puck02/Cling.git
    if ($LASTEXITCODE -ne 0) {
        Write-Host "错误: 克隆失败" -ForegroundColor Red
        exit 1
    }
}

# 进入目录
Set-Location Cling

# 编译测试
Write-Host "[4/4] 编译测试..." -ForegroundColor Yellow
$testFile = "exercises/00_intro/intro1.c"
if (Test-Path $testFile) {
    gcc $testFile -o test.exe
    if ($LASTEXITCODE -eq 0) {
        Write-Host "   编译成功!" -ForegroundColor Green
        Remove-Item test.exe -ErrorAction SilentlyContinue
    } else {
        Write-Host "   警告: 编译测试失败" -ForegroundColor Yellow
    }
}

Write-Host ""
Write-Host "==================================" -ForegroundColor Cyan
Write-Host "   安装完成!" -ForegroundColor Green
Write-Host "==================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "下一步:" -ForegroundColor Yellow
Write-Host "  1. cd Cling" -ForegroundColor Cyan
Write-Host "  2. cat README.md" -ForegroundColor Cyan
Write-Host "  3. 开始练习!" -ForegroundColor Cyan
Write-Host ""
