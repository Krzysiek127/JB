@echo off
cls
echo Compiling main project

REM Get current date and time
REM Made by chatgpt lol
for /f "tokens=2 delims==" %%I in ('wmic os get localdatetime /value') do set datetime=%%I

REM Extract date components
set year=%datetime:~0,4%
set month=%datetime:~4,2%
set day=%datetime:~6,2%

REM Extract time components
set hour=%datetime:~8,2%
set minute=%datetime:~10,2%

REM Echo formatted date and time
echo Beta build %day%.%month%.%year%-%hour%:%minute%

REM compile *.c, link with ws2_32 (socket lib), luuid lole32 (shell libs) and treat warnings as errors
gcc Main.c src\Socket.c src\Funnies.c src\Link.c -lWinmm -luuid -lole32 -lws2_32 -o Jailbreak.exe -Wall -Werror

if exist bell.exe .\bell.exe