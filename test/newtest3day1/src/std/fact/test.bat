@echo off
for /l %%i in (1,1,100000) do (
echo No.%%i
gen.exe
fact.exe
fact_mpfr.exe
fc fact.out fact.ans
if errorlevel 1 pause
)