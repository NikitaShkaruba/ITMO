@echo off
echo Building Lab5
masm lab5.asm lab5.obj NUL.LST NUL.CRF
link lab5.obj;
echo Project has been successfully builded. Come again ^)