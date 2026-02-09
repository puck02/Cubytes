# Windows Installer
[Console]::OutputEncoding=[System.Text.Encoding]::UTF8
Write-Host "Cling Installer" -ForegroundColor Green
if (!(Get-Command git -EA Silent)) { Write-Host "Need Git"; exit 1 }
if (Test-Path Cling) { cd Cling; git pull } else { git clone https://github.com/puck02/Cling.git; cd Cling }
try { Invoke-WebRequest -Uri https://github.com/puck02/Cling/releases/latest/download/cling-windows-x86_64.exe -OutFile cling.exe } catch {}
if (!(Test-Path mingw64\bin\gcc.exe)) { Invoke-WebRequest -Uri https://github.com/brechtsanders/winlibs_mingw/releases/download/13.2.0-16.0.6-11.0.0-ucrt-r1/winlibs-x86_64-posix-seh-gcc-13.2.0-mingw-w64ucrt-11.0.0-r1.zip -OutFile $env:TEMP\m.zip; Expand-Archive $env:TEMP\m.zip . -Force }
Write-Host "Done! Run: .\cling.exe watch"
