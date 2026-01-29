@echo off
setlocal

REM === Path to MinGW-w64 (adjust if needed) ===
set MINGW=D:\Koodiohjelmat\Cppcompiler\mingw64\bin

REM === Compiler ===
set CXX=%MINGW%\x86_64-w64-mingw32-g++

REM === Output ===
set OUT=./build/libsudoku.dll

REM === Build ===
%CXX% ^
  -std=c++20 ^
  -O2 ^
  -shared ^
  -DSUDOKU_EXPORTS ^
  -Iinclude ^
  ./sudoku/sudoku_api.cpp ^
  ./sudoku/sudoku.cpp ^
  ./sudoku/algx.cpp ^
  -o %OUT%

IF %ERRORLEVEL% NEQ 0 (
    echo Build FAILED
    pause
    exit /b 1
)

echo Build SUCCESS
echo Output: %OUT%
pause
