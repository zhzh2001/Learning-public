@echo off
for /l %%i in (1,1,1000000) do (
	echo No.%%i
	gen.exe
	corral.exe
	corral_enhanced.exe
	fc corral.out corral.ans
	if errorlevel 1 pause
)