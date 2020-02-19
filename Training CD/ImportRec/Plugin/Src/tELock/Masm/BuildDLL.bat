@echo off

if exist tELock.obj del tELock.obj
if exist tELock.dll del tELock.dll

\masm32\bin\ml /c /coff tELock.asm

\masm32\bin\Link /SUBSYSTEM:WINDOWS /DLL /DEF:tELock.def tELock.obj

dir tELock.*
pause
