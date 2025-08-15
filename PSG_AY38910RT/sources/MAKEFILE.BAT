@echo off
if exist build\ goto NEXTSTEP1
echo MAKEDIR build
md build
:NEXTSTEP1
echo Compiling Object
sdcc -mz80 -c -o build\  src\PSG_AY38910RT.c
pause
