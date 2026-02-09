# Cling Windows Installer
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

Write-Host "正在安装 Cling..." -ForegroundColor Green

# Check Git
if (!(Get-Command git -ErrorAction SilentlyContinue)) {
    Write-Host "错误: 需要先安装 Git" -ForegroundColor Red
    Write-Host "下载: https://git-scm.com/" -ForegroundColor Yellow
    exit 1
}

# Clone or update
if (Test-Path "Cling") {
    Write-Host "更新项目..." -ForegroundColor Yellow
    Set-Location Cling
    git pull origin main 2>$null
} else {
    Write-Host "下载项目..." -ForegroundColor Yellow
    git clone https://github.com/puck02/Cling.git
    if ($LASTEXITCODE -ne 0) {
        Write-Host "下载失败" -ForegroundColor Red
        exit 1
    }
    Set-Location Cling
}

# Download cling.exe
Write-Host "下载 Cling CLI..." -ForegroundColor Yellow
if (!(Test-Path "cling.exe")) {
    try {
        $ProgressPreference = 'SilentlyContinue'
        Invoke-WebRequest -Uri "https://github.com/puck02/Cling/releases/latest/download/cling-windows-x86_64.exe" -OutFile "cling.exe" -UseBasicParsing
        Write-Host "Cling CLI 下载完成" -ForegroundColor Green
    } catch {
        Write-Host "Cling CLI 下载失败（可选）" -ForegroundColor Yellow
    }
}

# Download MinGW
Write-Host "下载 GCC 编译器..." -ForegroundColor Yellow
if (!(Test-Path "mingw64\bin\gcc.exe")) {
    try {
        $url = "https://github.com/brechtsanders/winlibs_mingw/releases/download/13.2.0-16.0.6-11.0.0-ucrt-r1/winlibs-x86_64-posix-seh-gcc-13.2.0-mingw-w64ucrt-11.0.0-r1.zip"
        $zip = "$env:TEMP\mingw.zip"
        Write-Host "下载中 (约60MB)..." -ForegroundColor Cyan
        Invoke-WebRequest -Uri $url -OutFile $zip -UseBasicParsing
        Write-Host "解压中..." -ForegroundColor Cyan
        Expand-Archive -Path $zip -DestinationPath . -Force
        Remove-Item $zip -ErrorAction SilentlyContinue
        Write-Host "GCC 安装完成" -ForegroundColor Green
    } catch {
        Write-Host "GCC 下载失败" -ForegroundColor Red
        exit 1
    }
} else {
    Write-Host "GCC 已存在" -ForegroundColor Green
}

# Create cling.bat wrapper
$batContent = @"
@echo off
"%~dp0cling.exe" %*
"@
Set-Content -Path "cling.bat" -Value $batContent -Encoding ASCII

# Create PowerShell wrapper for PATH
$pathScript = @"
`$env:Path = "`$PSScriptRoot;`$PSScriptRoot\mingw64\bin;`$env:Path"
& "`$PSScriptRoot\cling.exe" @args
"@
Set-Content -Path "cling.ps1" -Value $pathScript -Encoding UTF8

Write-Host ""
Write-Host "=========================" -ForegroundColor Green
Write-Host "  安装完成！" -ForegroundColor Green
Write-Host "=========================" -ForegroundColor Green
Write-Host ""
Write-Host "快速开始:" -ForegroundColor Yellow
if (Test-Path "cling.exe") {
    Write-Host ""
    Write-Host "  .\cling watch" -ForegroundColor Cyan -BackgroundColor DarkGray
    Write-Host ""
    Write-Host "注意: PowerShell 需要用 .\ 前缀来运行当前目录的程序" -ForegroundColor DarkYellow
    Write-Host ""
    Write-Host "然后修改 exercises 目录下的练习文件即可自动编译测试！" -ForegroundColor White
} else {
    Write-Host "  .\mingw64\bin\gcc.exe exercises\00_intro\intro1.c -o intro1.exe" -ForegroundColor Cyan
    Write-Host "  .\intro1.exe" -ForegroundColor Cyan
}
Write-Host ""
