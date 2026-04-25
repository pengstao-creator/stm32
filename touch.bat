@echo off
setlocal enabledelayedexpansion

cd /d "%~dp0"

set "INPUT_PATH=%~1"
if "%INPUT_PATH%"=="" (
    echo [ERROR] Usage: .\touch.bat path
    echo [ERROR] Example: .\touch.bat App\pwm
    exit /b 1
)

set "INPUT_PATH=%INPUT_PATH:/=\%"
if "%INPUT_PATH:~0,2%"==".\" set "INPUT_PATH=%INPUT_PATH:~2%"

for %%I in ("%INPUT_PATH%") do (
    set "EXT=%%~xI"
)

if "%EXT%"=="" (
    call :create_file "%INPUT_PATH%.h"
    if errorlevel 1 exit /b 1
    call :create_file "%INPUT_PATH%.c"
    exit /b %errorlevel%
)

call :create_file "%INPUT_PATH%"
exit /b %errorlevel%

:create_file
set "REL_PATH=%~1"
for %%I in ("%REL_PATH%") do (
    set "BASE_NAME=%%~nI"
    set "EXT=%%~xI"
    set "DIR_REL=%%~dpI"
)

if /i not "%EXT%"==".h" if /i not "%EXT%"==".c" (
    echo [ERROR] Only .h/.c supported: %REL_PATH%
    exit /b 1
)

if "%DIR_REL%"=="" set "DIR_REL=."
if not exist "%DIR_REL%" mkdir "%DIR_REL%"

if exist "%REL_PATH%" (
    echo [WARN] %REL_PATH% exists, skip
    exit /b 0
)

if /i "%EXT%"==".h" (
    set "HEADER_GUARD=%BASE_NAME%"
    set "HEADER_GUARD=!HEADER_GUARD:-=_!"
    set "HEADER_GUARD=!HEADER_GUARD:.=_!"
    set "HEADER_GUARD=!HEADER_GUARD:a=A!"
    set "HEADER_GUARD=!HEADER_GUARD:b=B!"
    set "HEADER_GUARD=!HEADER_GUARD:c=C!"
    set "HEADER_GUARD=!HEADER_GUARD:d=D!"
    set "HEADER_GUARD=!HEADER_GUARD:e=E!"
    set "HEADER_GUARD=!HEADER_GUARD:f=F!"
    set "HEADER_GUARD=!HEADER_GUARD:g=G!"
    set "HEADER_GUARD=!HEADER_GUARD:h=H!"
    set "HEADER_GUARD=!HEADER_GUARD:i=I!"
    set "HEADER_GUARD=!HEADER_GUARD:j=J!"
    set "HEADER_GUARD=!HEADER_GUARD:k=K!"
    set "HEADER_GUARD=!HEADER_GUARD:l=L!"
    set "HEADER_GUARD=!HEADER_GUARD:m=M!"
    set "HEADER_GUARD=!HEADER_GUARD:n=N!"
    set "HEADER_GUARD=!HEADER_GUARD:o=O!"
    set "HEADER_GUARD=!HEADER_GUARD:p=P!"
    set "HEADER_GUARD=!HEADER_GUARD:q=Q!"
    set "HEADER_GUARD=!HEADER_GUARD:r=R!"
    set "HEADER_GUARD=!HEADER_GUARD:s=S!"
    set "HEADER_GUARD=!HEADER_GUARD:t=T!"
    set "HEADER_GUARD=!HEADER_GUARD:u=U!"
    set "HEADER_GUARD=!HEADER_GUARD:v=V!"
    set "HEADER_GUARD=!HEADER_GUARD:w=W!"
    set "HEADER_GUARD=!HEADER_GUARD:x=X!"
    set "HEADER_GUARD=!HEADER_GUARD:y=Y!"
    set "HEADER_GUARD=!HEADER_GUARD:z=Z!"
    (
        echo #ifndef __!HEADER_GUARD!_H
        echo #define __!HEADER_GUARD!_H
        echo.
        echo #include "system.h"
        echo.
        echo #endif
    ) > "%REL_PATH%"
    echo [OK] created: %REL_PATH%
    exit /b 0
)

(
    echo #include "%BASE_NAME%.h"
    echo.
) > "%REL_PATH%"
echo [OK] created: %REL_PATH%
exit /b 0
