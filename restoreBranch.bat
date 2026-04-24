@echo off
setlocal enabledelayedexpansion

cd /d "%~dp0"

git rev-parse --is-inside-work-tree >nul 2>&1
if errorlevel 1 (
    echo [ERROR] 当前目录不是 Git 仓库: %cd%
    exit /b 1
)

set "TARGET_BRANCH=%~1"

git fetch --all --prune
if errorlevel 1 (
    echo [ERROR] git fetch 失败
    exit /b 1
)

if not "%TARGET_BRANCH%"=="" goto :restore_one
goto :restore_all

:restore_one
set "TARGET_REMOTE_REF="
for /f "usebackq delims=" %%R in (`git for-each-ref --format="%%(refname:short)" refs/remotes`) do (
    set "remote_ref=%%~R"
    if /i not "!remote_ref:~-5!"=="/HEAD" (
        set "branch_name="
        for /f "tokens=1,* delims=/" %%A in ("!remote_ref!") do (
            set "branch_name=%%B"
        )
        if /i "!branch_name!"=="%TARGET_BRANCH%" (
            if not defined TARGET_REMOTE_REF set "TARGET_REMOTE_REF=!remote_ref!"
        )
    )
)

if not defined TARGET_REMOTE_REF (
    echo [ERROR] 远端不存在分支: %TARGET_BRANCH%
    exit /b 1
)

git show-ref --verify --quiet "refs/heads/%TARGET_BRANCH%"
if errorlevel 1 (
    git branch --track "%TARGET_BRANCH%" "%TARGET_REMOTE_REF%"
    if errorlevel 1 (
        echo [ERROR] 创建本地分支失败: %TARGET_BRANCH%
        exit /b 1
    )
    echo [OK] 已创建本地分支: %TARGET_BRANCH% ^<=^> %TARGET_REMOTE_REF%
) else (
    echo [INFO] 本地分支已存在，跳过: %TARGET_BRANCH%
)
exit /b 0

:restore_all
set /a created=0
set /a skipped=0
for /f "usebackq delims=" %%R in (`git for-each-ref --format="%%(refname:short)" refs/remotes`) do (
    set "remote_ref=%%~R"
    if /i not "!remote_ref:~-5!"=="/HEAD" (
        set "branch_name="
        for /f "tokens=1,* delims=/" %%A in ("!remote_ref!") do (
            set "branch_name=%%B"
        )
        if defined branch_name (
            rem 本地不存在时才创建并关联到对应远端分支
            git show-ref --verify --quiet "refs/heads/!branch_name!"
            if errorlevel 1 (
                git branch --track "!branch_name!" "!remote_ref!"
                if errorlevel 1 (
                    echo [WARN] 创建失败: !branch_name! ^<=^> !remote_ref!
                ) else (
                    set /a created+=1
                )
            ) else (
                set /a skipped+=1
            )
        )
    )
)

echo [OK] 恢复完成: 新建 !created! 个，已存在跳过 !skipped! 个
exit /b 0
