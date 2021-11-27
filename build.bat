@echo off

if not exist "bin" (
    mkdir bin
)

if exist "src\main.cpp" (
    g++ src\main.cpp -o bin\env-var-parser.exe
) else (
    echo [-] Error! Source code not found.
)
