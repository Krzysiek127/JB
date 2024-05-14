@echo off
cls
cd /d %~dp0

rd /s /q "%~dp0res"
del /f /q Jailbreak.exe

rem S L I C K
(goto) 2>nul & del "%~f0"