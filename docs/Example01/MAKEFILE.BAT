@echo off
REM MAKEFILE for 8/16K ROMs using SDCC compiler
SET CFILENAME=Example01
if exist build\ goto NEXTSTEP1
md build
goto COMPILA
:NEXTSTEP1
REM get SDCC version
sdcc -v
echo Delete build...
del build\*.* /Q
:COMPILA
echo Compiling...
sdcc -mz80 -o build\ --code-loc 0x4020 --data-loc 0xC000 --use-stdout --no-std-crt0 crt0_MSX816kROM4000.rel PSG_AY38910RT.rel %CFILENAME%.c
if not exist build\%CFILENAME%.ihx goto SALIDA
hex2bin -e ROM -l 2000 build\%CFILENAME%.ihx
copy build\%CFILENAME%.ROM
pause
exit /b
:SALIDA
echo ERROR in Compile
pause
exit /b