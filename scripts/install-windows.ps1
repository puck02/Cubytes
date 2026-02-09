# Cling 一键安装脚本 (Windows)
# ⚠️ 此脚本已弃用，请使用新的便携版脚本

# 设置控制台编码为 UTF-8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8
chcp 65001 > $null

Write-Host ""
Write-Host "========================================" -ForegroundColor Red
Write-Host "  ⚠️  此安装脚本已弃用" -ForegroundColor Yellow
Write-Host "========================================" -ForegroundColor Red
Write-Host ""
Write-Host "请使用新的便携版安装脚本:" -ForegroundColor Yellow
Write-Host ""
Write-Host "irm https://raw.githubusercontent.com/puck02/Cling/main/scripts/install-portable.ps1 | iex" -ForegroundColor Cyan
Write-Host ""
Write-Host "新脚本特点:" -ForegroundColor Green
Write-Host "  ✓ 不会弹出安装窗口" -ForegroundColor White
Write-Host "  ✓ 不会修改系统" -ForegroundColor White
Write-Host "  ✓ 纯下载方案，安全可靠" -ForegroundColor White
Write-Host ""
Write-Host "按任意键退出..." -ForegroundColor Yellow
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
exit 0

# 检查是否安装了 GCC
Write-Host "[1/5] 检查 GCC..." -ForegroundColor Yellow
$gccPath = Get-Command gcc -ErrorAction SilentlyContinue
if (-not $gccPath) {
    Write-Host "   未找到 GCC，正在下载便携版..." -ForegroundColor Yellow
    
    # 下载 WinLibs MinGW（便携版，无需安装）
    $mingwUrl = "https://github.com/brechtsanders/winlibs_mingw/releases/download/13.2.0-16.0.6-11.0.0-ucrt-r1/winlibs-x86_64-posix-seh-gcc-13.2.0-mingw-w64ucrt-11.0.0-r1.zip"
    $mingwZip = "$env:TEMP\mingw.zip"
    $mingwDir = "$PWD\mingw64"
    
    try {
        Write-Host "   下载中... (约 60MB)" -ForegroundColor Cyan
        $ProgressPreference = 'SilentlyContinue'
        Invoke-WebRequest -Uri $mingwUrl -OutFile $mingwZip -UseBasicParsing
        
        Write-Host "   解压中..." -ForegroundColor Cyan
        Expand-Archive -Path $mingwZip -DestinationPath $PWD -Force
        
        # 清理
        Remove-Item $mingwZip -ErrorAction SilentlyContinue
        
        # 添加到当前会话的 PATH
        $env:Path = "$mingwDir\bin;$env:Path"
        
        Write-Host "   MinGW 已安装到: $mingwDir" -ForegroundColor Green
        Write-Host "   提示: 这是便携版，只在当前项目中使用" -ForegroundColor Yellow
    } catch {
        Write-Host "错误: 下载失败 - $_" -ForegroundColor Red
        Write-Host "请检查网络连接或手动下载 MinGW" -ForegroundColor Yellow
        exit 1
    }
} else {
    Write-Host "   已找到 GCC: $($gccPath.Source)" -ForegroundColor Green
}

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
    # 使用便携版 GCC 或系统 GCC
    $gccExe = if (Test-Path "mingw64\bin\gcc.exe") { "mingw64\bin\gcc.exe" } else { "gcc" }
    & $gccExe $testFile -o test.exe
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
Write-Host "  2. 编译练习: .\mingw64\bin\gcc.exe exercises\00_intro\intro1.c -o intro1.exe" -ForegroundColor Cyan
Write-Host "  3. 或查看 README.md 了解更多" -ForegroundColor Cyan
Write-Host ""
Write-Host "提示: 便携版 GCC 在 Cling\mingw64 目录" -ForegroundColor Yellow
Write-Host ""
