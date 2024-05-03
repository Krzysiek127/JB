@echo off
cls
echo Compiling csend

REM compile csend.c with Telthar socket wrapper, link with ws2_32 (socket lib) and treat warnings as errors
gcc csend.c ..\src\Socket.c -o csend.exe -lws2_32 -Wall -Werror