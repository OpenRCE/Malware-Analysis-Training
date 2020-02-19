@echo off

if exist tELock.obj del tELock.obj
if exist tELock.dll del tELock.dll

\Tasm\bin\tasm32 /ml /m tELock.asm
\Tasm\bin\tlink32 /Tpd /aa /c /V4.0 /x tELock,tELock,,c:\tasm\lib\import32,tELock.def

dir tELock.*
pause
