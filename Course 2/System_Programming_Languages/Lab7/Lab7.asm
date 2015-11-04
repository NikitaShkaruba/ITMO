.386					
.model flat, stdcall
option casemap: none

; *************************************************************************
; MASM32 prototypes for Win32 functions and structures
include c:\masm32\include\windows.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\masm32.inc
include \masm32\macros\macros.asm
; *************************************************************************
; MASM32 object libraries
includelib c:\masm32\lib\kernel32.lib
includelib c:\masm32\lib\masm32.lib
; *************************************************************************  
; C function
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
; *************************************************************************

.stack 100h

.data
	x1 dq 1.4
	x2 dq 1.4
	a dq 1.6
	prec dq 0.001
	endl db 10, 8, 0
	tab db 9, 0
	wall db ' ', '|', ' ', 0
.data?
	strBuffer db 20 dup(?)
	
.code
SinSum proc xPtr:dword, aPtr:dword, precPtr:dword	
	finit
	
	mov edx, precPtr
	mov eax, xPtr
	mov ebx, aPtr
	
	fld qword ptr [edx] ; st(3) = prec
	fldz				; st(2) = 0. 	SUM
	fld qword ptr [ebx]	; st(1) = a		TEMP
	fld qword ptr [eax]	; st(0) = x 

nextIter:
	fadd st(0), st(1)
	
	fstp qword ptr [eax]
	
	ret 6
SinSum endp

start:
	; print x befor
	invoke FloatToStr, x1, offset strBuffer
	print addr wall
	print addr strBuffer
	print addr tab
	
	; print x after
	invoke SinSum, offset x1, offset a, offset prec
	invoke FloatToStr, x1, offset strBuffer
	print addr wall
	print addr strBuffer
	print addr tab
	
	; TODO: print range length
	
	; print c function
	invoke crt_cos, x2
	lea eax, x2
	fstp qword ptr [eax]
	invoke FloatToStr, x2, offset strBuffer
	print addr wall
	print addr strBuffer
	print addr tab
	print addr wall
	
    invoke ExitProcess, 0
end start
