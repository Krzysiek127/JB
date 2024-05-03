@echo off
cls
echo Compiling main project

REM compile *.c, link with ws2_32 (socket lib) and treat warnings as errors
gcc Main.c src\Socket.c src\Funnies.c -o Jailbreak.exe -lws2_32 -lWinmm -Wall -Werror