# Cling 一键安装脚本 (Windows PowerShell)
# 使用方法: 以管理员身份运行 PowerShell，执行:
# iwr -useb https://raw.githubusercontent.com/puck02/Cling/main/scripts/install.ps1 | iex

$ErrorActionPreference = "Stop"

Write-Host ""
Write-Host "  _____ _ _             " -ForegroundColor Cyan
Write-Host " / ____| (_)            " -ForegroundColor Cyan
Write-Host "| |    | |_ _ __   __ _ " -ForegroundColor Cyan
Write-Host "| |    | | | '_ \ / _`` |" -ForegroundColor Cyan
Write-Host "| |____| | | | | | (_| |" -ForegroundColor Cyan
Write-Host " \_____|_|_|_| |_|\__, |" -ForegroundColor Cyan
Write-Host "                   __/ |" -ForegroundColor Cyan
Write-Host "                  |___/ " -ForegroundColor Cyan
Write-Host ""
Write-Host "Cling - C语言快速入门练习系统" -ForegroundColor Green
Write-Host ""

# 检查是否以管理员身份运行
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if (-not $isAdmin) {
    Write-Host "请以管理员身份运行此脚本！" -ForegroundColor Red
    Write-Host "右键点击 PowerShell -> 以管理员身份运行" -ForegroundColor Yellow
    exit 1
}

# 检查并安装Chocolatey
Write-Host "[1/4] 检查包管理器..." -ForegroundColor Blue

if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
    Write-Host "  未找到Chocolatey，正在安装..." -ForegroundColor Yellow
    Set-ExecutionPolicy Bypass -Scope Process -Force
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
    Invoke-Expression ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
    
    # 刷新环境变量
    $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
    
    Write-Host "  ✓ Chocolatey 安装完成" -ForegroundColor Green
} else {
    Write-Host "  ✓ 已安装 Chocolatey" -ForegroundColor Green
}

# 检查并安装MinGW (GCC)
Write-Host ""
Write-Host "[2/4] 检查C编译器 (MinGW-w64)..." -ForegroundColor Blue

if (-not (Get-Command gcc -ErrorAction SilentlyContinue)) {
    Write-Host "  未找到GCC，正在安装MinGW-w64..." -ForegroundColor Yellow
    choco install mingw -y
    
    # 刷新环境变量
    $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
    
    Write-Host "  ✓ MinGW-w64 安装完成" -ForegroundColor Green
} else {
    $gccVersion = gcc --version | Select-Object -First 1
    Write-Host "  ✓ 已安装 $gccVersion" -ForegroundColor Green
}

# 检查并安装CMake
Write-Host ""
Write-Host "[3/4] 检查CMake..." -ForegroundColor Blue

if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    Write-Host "  未找到CMake，正在安装..." -ForegroundColor Yellow
    choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System' -y
    
    # 刷新环境变量
    $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
    
    Write-Host "  ✓ CMake 安装完成" -ForegroundColor Green
} else {
    $cmakeVersion = cmake --version | Select-Object -First 1
    Write-Host "  ✓ 已安装 $cmakeVersion" -ForegroundColor Green
}

# 下载并安装Cling
Write-Host ""
Write-Host "[4/4] 安装Cling..." -ForegroundColor Blue

$ClingVersion = "v0.1.0"
$InstallDir = "$env:LOCALAPPDATA\Cling"
$DownloadUrl = "https://github.com/puck02/Cling/releases/download/$ClingVersion/cling-windows-x86_64.exe"

# 创建安装目录
if (-not (Test-Path $InstallDir)) {
    New-Item -ItemType Directory -Path $InstallDir -Force | Out-Null
}

Write-Host "  下载 cling-windows-x86_64.exe..." -ForegroundColor White
$ProgressPreference = 'SilentlyContinue'
Invoke-WebRequest -Uri $DownloadUrl -OutFile "$InstallDir\cling.exe"
$ProgressPreference = 'Continue'

# 添加到PATH
$currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($currentPath -notlike "*$InstallDir*") {
    [Environment]::SetEnvironmentVariable("Path", "$currentPath;$InstallDir", "User")
    $env:Path = "$env:Path;$InstallDir"
    Write-Host "  已添加到系统PATH" -ForegroundColor White
}

Write-Host "  ✓ Cling 安装完成" -ForegroundColor Green

# 验证安装
Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "✓ 安装完成！" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""

Write-Host "验证安装:" -ForegroundColor White
Write-Host "  gcc --version" -ForegroundColor Gray
gcc --version 2>$null | Select-Object -First 1

Write-Host "  cmake --version" -ForegroundColor Gray
cmake --version 2>$null | Select-Object -First 1

Write-Host "  cling (已安装到 $InstallDir)" -ForegroundColor Gray

Write-Host ""
Write-Host "开始学习:" -ForegroundColor Blue
Write-Host "  1. 克隆练习仓库:" -ForegroundColor White
Write-Host "     git clone https://github.com/puck02/Cling.git" -ForegroundColor Gray
Write-Host "     cd Cling" -ForegroundColor Gray
Write-Host ""
Write-Host "  2. 启动学习:" -ForegroundColor White
Write-Host "     cling watch" -ForegroundColor Gray
Write-Host ""
Write-Host "注意: 请重新打开终端以使PATH生效！" -ForegroundColor Yellow
Write-Host ""
Write-Host "祝你学习愉快！🎉" -ForegroundColor Yellow
