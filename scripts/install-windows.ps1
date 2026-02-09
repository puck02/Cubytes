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
Write-Host "[1/5] 检查 GCC..." -ForegroundColor Yellow
$gccPath = Get-Command gcc -ErrorAction SilentlyContinue
if (-not $gccPath) {
    Write-Host "   未找到 GCC，正在自动安装..." -ForegroundColor Yellow
    
    # 尝试使用 winget 安装
    $wingetPath = Get-Command winget -ErrorAction SilentlyContinue
    if ($wingetPath) {
        Write-Host "   使用 winget 安装 MinGW..." -ForegroundColor Cyan
        winget install -e --id MSYS2.MSYS2 --silent --accept-source-agreements --accept-package-agreements
        
        # 添加 MSYS2 到 PATH（用户级别）
        $msys2Path = "C:\msys64\mingw64\bin"
        if (Test-Path $msys2Path) {
            $currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
            if ($currentPath -notlike "*$msys2Path*") {
                [Environment]::SetEnvironmentVariable("Path", "$currentPath;$msys2Path", "User")
                $env:Path = "$env:Path;$msys2Path"
                Write-Host "   已将 MinGW 添加到 PATH" -ForegroundColor Green
            }
            
            # 安装 GCC 工具链
            Write-Host "   正在安装 GCC 工具链..." -ForegroundColor Cyan
            & "C:\msys64\usr\bin\bash.exe" -lc "pacman -S --noconfirm mingw-w64-x86_64-gcc"
        }
    } else {
        # 尝试使用 chocolatey
        $chocoPath = Get-Command choco -ErrorAction SilentlyContinue
        if ($chocoPath) {
            Write-Host "   使用 Chocolatey 安装 MinGW..." -ForegroundColor Cyan
            choco install mingw -y
        } else {
            Write-Host "错误: 无法自动安装 GCC" -ForegroundColor Red
            Write-Host "请手动安装以下任一工具:" -ForegroundColor Yellow
            Write-Host "  1. MSYS2: https://www.msys2.org/" -ForegroundColor Cyan
            Write-Host "  2. 或安装 winget: winget install Microsoft.VisualStudio.2022.BuildTools" -ForegroundColor Cyan
            exit 1
        }
    }
    
    # 重新检查 GCC
    $gccPath = Get-Command gcc -ErrorAction SilentlyContinue
    if (-not $gccPath) {
        Write-Host "警告: GCC 安装完成，但需要重启终端" -ForegroundColor Yellow
        Write-Host "请关闭此窗口，重新打开 PowerShell 后再次运行安装脚本" -ForegroundColor Cyan
        exit 0
    }
}
Write-Host "   已找到 GCC: $($gccPath.Source)" -ForegroundColor Green

# 检查是否安装了 Git
Write-Host "[2/5] 检查 Git..." -ForegroundColor Yellow
$gitPath = Get-Command git -ErrorAction SilentlyContinue
if (-not $gitPath) {
    Write-Host "错误: 未找到 Git" -ForegroundColor Red
    Write-Host "请先安装 Git: https://git-scm.com/" -ForegroundColor Cyan
    exit 1
}
Write-Host "   已找到 Git: $($gitPath.Source)" -ForegroundColor Green

# 克隆仓库
Write-Host "[3/5] 下载 Cling..." -ForegroundColor Yellow
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
Write-Host "[4/5] 编译测试..." -ForegroundColor Yellow
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
Write-Host "[5/5] 设置完成..." -ForegroundColor Yellow
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
Write-Host "注意: 如果遇到 gcc 命令未找到，请重启终端" -ForegroundColor Yellow
Write-Host ""
