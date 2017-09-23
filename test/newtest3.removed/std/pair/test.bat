@echo off
for /l %%i in (1,1,10000) do (
echo No.%%i
gen.exe
pair.exe
pair_bl.exe
fc pair.out pair.ans
if errorlevel 1 pause
pair_sweep_line.exe
fc pair.out pair.ans
if errorlevel 1 pause
)