@echo off  
:loop  
    rand.exe %random% > data.in
    start python std.py
    my.exe < data.in > my.out
    ping -n 5 127.0.0.1>nul
    fc my.out std.out 
if not errorlevel 1 goto loop  
pause
goto loop