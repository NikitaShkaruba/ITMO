@echo off

if exist Lab7.obj del Lab7.obj
if exist Lab7.exe del Lab7.exe

ml /c /coff Lab7.asm
if errorlevel 1 goto errasm

if not exist rsrc.obj goto nores

Link /SUBSYSTEM:CONSOLE /OPT:NOREF Lab7.obj rsrc.obj
if errorlevel 1 goto errlink

dir Lab7.*
goto TheEnd

:nores
Link /SUBSYSTEM:CONSOLE /OPT:NOREF Lab7.obj
if errorlevel 1 goto errlink
dir Lab7.*
goto TheEnd

:errlink
echo _
echo Link error
goto TheEnd

:errasm
echo _
echo Assembly Error
goto TheEnd

:TheEnd

pause
