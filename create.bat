@echo off
setlocal
chcp 65001 >nul

REM 切换到脚本所在目录（建议脚本放在仓库根目录）
cd /d "%~dp0"

REM 基础检查：必须是 git 仓库
if not exist ".git" (
    echo [ERROR] 当前目录不是 Git 仓库根目录: %cd%
    goto :fail
)

REM 1) 输入项目名称 x，并创建新分支
set "PROJECT_NAME=%~1"
if not "%PROJECT_NAME%"=="" goto :name_ok

:input_name
set "PROJECT_NAME="
set /p PROJECT_NAME=请输入项目名称(将作为分支名和提交信息): 
if "%PROJECT_NAME%"=="" (
    echo [WARN] 项目名称不能为空，请重新输入。
    goto :input_name
)

:name_ok

echo [INFO] 创建并切换分支: %PROJECT_NAME%
git checkout -b "%PROJECT_NAME%"
if errorlevel 1 (
    echo [ERROR] 创建并切换分支失败（可能分支已存在）
    goto :fail
)

REM 2) 在 App 目录创建 x.h 和 x.c
if not exist "App" (
    echo [ERROR] 未找到 App 目录
    goto :fail
)

if not exist "touch.bat" (
    echo [ERROR] 未找到 touch.bat
    goto :fail
)

call "%~dp0touch.bat" "App\%PROJECT_NAME%"
if errorlevel 1 goto :fail

REM 3) git add . 并以项目名称提交
git add .
if errorlevel 1 (
    echo [ERROR] git add 失败
    goto :fail
)

git commit -m "%PROJECT_NAME%"
if errorlevel 1 (
    echo [ERROR] git commit 失败（常见原因：没有可提交内容）
    goto :fail
)

echo [OK] 全部完成
pause
exit /b 0

:fail
echo [INFO] 当前 Git 状态：
git status --short
pause
exit /b 1
