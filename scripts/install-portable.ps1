# Cling 便携版安装脚本 (Windows)
# 完全不依赖系统安装工具，纯下载方案

# 设置控制台编码为 UTF-8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8
chcp 65001 > $null

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  🐍 Cling C语言学习系统 (便携版)" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# 步骤 1: 检查 Git
Write-Host "[1/4] 检查 Git..." -ForegroundColor Yellow
$gitPath = Get-Command git -ErrorAction SilentlyContinue
if (-not $gitPath) {
    Write-Host "  ❌ 未找到 Git" -ForegroundColor Red
    Write-Host ""
    Write-Host "请先安装 Git:" -ForegroundColor Yellow
    Write-Host "  下载: https://git-scm.com/download/win" -ForegroundColor Cyan
    Write-Host "  或使用命令: winget install Git.Git" -ForegroundColor Cyan
    Write-Host ""
    exit 1
}
Write-Host "  ✓ Git 已安装" -ForegroundColor Green

# 步骤 2: 克隆仓库
Write-Host ""
Write-Host "[2/4] 下载 Cling 项目..." -ForegroundColor Yellow
if (Test-Path "Cling") {
    Write-Host "  ⚠ 目录已存在，使用现有版本" -ForegroundColor Yellow
    Set-Location Cling
    git pull origin main 2>$null
} else {
    git clone https://github.com/puck02/Cling.git
    if ($LASTEXITCODE -ne 0) {
        Write-Host "  ❌ 下载失败" -ForegroundColor Red
        exit 1
    }
    Set-Location Cling
    Write-Host "  ✓ 项目已下载" -ForegroundColor Green
}

# 步骤 3: 下载便携版 MinGW
Write-Host ""
Write-Host "[3/4] 下载便携版 GCC 编译器..." -ForegroundColor Yellow

$gccPath = Get-Command gcc -ErrorAction SilentlyContinue
if ($gccPath) {
    Write-Host "  ✓ 系统已有 GCC: $($gccPath.Source)" -ForegroundColor Green
} elseif (Test-Path "mingw64\bin\gcc.exe") {
    Write-Host "  ✓ 便携版 GCC 已存在" -ForegroundColor Green
    $env:Path = "$PWD\mingw64\bin;$env:Path"
} else {
    Write-Host "  📦 下载中... (约 60MB，请稍候)" -ForegroundColor Cyan
    
    $mingwUrl = "https://github.com/brechtsanders/winlibs_mingw/releases/download/13.2.0-16.0.6-11.0.0-ucrt-r1/winlibs-x86_64-posix-seh-gcc-13.2.0-mingw-w64ucrt-11.0.0-r1.zip"
    $mingwZip = "$env:TEMP\cling_mingw.zip"
    
    try {
        # 显示下载进度
        $ProgressPreference = 'Continue'
        Invoke-WebRequest -Uri $mingwUrl -OutFile $mingwZip -UseBasicParsing
        
        Write-Host "  📂 解压中..." -ForegroundColor Cyan
        $ProgressPreference = 'SilentlyContinue'
        Expand-Archive -Path $mingwZip -DestinationPath . -Force
        
        Remove-Item $mingwZip -ErrorAction SilentlyContinue
        
        $env:Path = "$PWD\mingw64\bin;$env:Path"
        Write-Host "  ✓ GCC 已安装到: mingw64\" -ForegroundColor Green
    } catch {
        Write-Host "  ❌ 下载失败: $_" -ForegroundColor Red
        Write-Host ""
        Write-Host "备选方案:" -ForegroundColor Yellow
        Write-Host "  1. 检查网络连接后重试" -ForegroundColor Cyan
        Write-Host "  2. 手动下载: $mingwUrl" -ForegroundColor Cyan
        Write-Host "  3. 解压到当前目录的 mingw64 文件夹" -ForegroundColor Cyan
        exit 1
    }
}

# 步骤 4: 测试编译
Write-Host ""
Write-Host "[4/4] 测试编译..." -ForegroundColor Yellow

$testFile = "exercises\00_intro\intro1.c"
if (Test-Path $testFile) {
    $gccExe = if (Test-Path "mingw64\bin\gcc.exe") { 
        "mingw64\bin\gcc.exe" 
    } else { 
        "gcc" 
    }
    
    & $gccExe $testFile -o test_intro.exe 2>&1 | Out-Null
    
    if (Test-Path "test_intro.exe") {
        Write-Host "  ✓ 编译测试成功！" -ForegroundColor Green
        Remove-Item test_intro.exe -ErrorAction SilentlyContinue
    } else {
        Write-Host "  ⚠ 编译测试失败（可忽略）" -ForegroundColor Yellow
    }
}

# 完成提示
Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  ✨ 安装完成！" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "📚 快速开始 (Windows 简化版):" -ForegroundColor Yellow
Write-Host ""

if (Test-Path "mingw64\bin\gcc.exe") {
    Write-Host "📝 第一个练习:" -ForegroundColor Cyan
    Write-Host "  .\mingw64\bin\gcc.exe exercises\00_intro\intro1.c -o intro1.exe" -ForegroundColor White
    Write-Host "  .\intro1.exe" -ForegroundColor White
    Write-Host ""
    Write-Host "🎯 继续练习:" -ForegroundColor Cyan
    Write-Host "  1. 打开 exercises 文件夹" -ForegroundColor White
    Write-Host "  2. 修改 .c 文件完成 TODO" -ForegroundColor White
    Write-Host "  3. 编译并运行测试" -ForegroundColor White
} else {
    Write-Host "编译示例:" -ForegroundColor Cyan
    Write-Host "  gcc exercises\00_intro\intro1.c -o intro1.exe" -ForegroundColor White
    Write-Host "  .\intro1.exe" -ForegroundColor White
}

Write-Host ""
Write-Host "📖 查看所有练习:" -ForegroundColor Cyan
Write-Host "  type README.md" -ForegroundColor White
Write-Host ""
Write-Host "⚠️  注意:" -ForegroundColor Yellow
Write-Host "  Windows 版本使用手动编译方式" -ForegroundColor White
Write-Host "  高级用户可安装 Rust 后使用 'cargo run -- watch' 自动监控" -ForegroundColor White
Write-Host ""
Write-Host "💡 提示: 便携版 GCC 在 mingw64 文件夹中" -ForegroundColor Yellow
Write-Host ""
