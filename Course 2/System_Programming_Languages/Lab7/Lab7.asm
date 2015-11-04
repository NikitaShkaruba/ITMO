.386					; Enable 80386+ instruction set
.model flat, stdcall	; Flat, 32-bit memory model (not used in 64-bit)
option casemap: none	; Case sensitive syntax

; *************************************************************************
; MASM32 proto types for Win32 functions and structures
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
	x1 dq 0.2
	deltaX dq 0.2
	xn dq 2.0
	a dq 1.6
	prec dq 0.0001
	
	endl db 10, 8, 0
	tab db 9, 0
	wall db ' ', '|', ' ', 0
.data?
	strBuffer db 20 dup(?)
	rangeLength dw ?
	
.code
SinSum proc xPtr:dword, aPtr:dword, precPtr:dword	
	local i:word
	pusha
	mov i, 0
	
	mov ecx, precPtr	; 0.001
	mov ebx, aPtr		; 1.6
	mov eax, xPtr		; 1.8
	lea edx, i
	mov rangeLength, 0
	
	fldz				; st(2) = 0. 		SUM
	fld qword ptr [ecx] ; st(1) = prec		PREC

nextIter:
	fild word ptr ss:[edx]	; st(0) = i		TEMP
	
	fldpi
	fmulp st(1), st(0)	; st(0) = i*pi
	
	fld1
	fld1
	faddp st(1), st(0)
	fdivp st(1), st(0)	; st(0) = i*pi/2
	
	fld qword ptr [ebx]
	faddp st(1), st(0)	; st(0) = (a + i*pi/2)
	
	fsin				; st(0) = sin(a + i*pi/2)

pow:
	xor ecx, ecx
	mov cx,  i
	cmp cx, 0
	je faq
	fld1				
	fld qword ptr [eax]
powLoop:
	fmul st(1), st(0)	; st(1) *= x
	loop powLoop
	
	faddp st(0), st(0)
	fmulp st(1), st(0)	; st(0) = (x^i)*sin(a + i*pi/2)
	
faq:
	xor ecx, ecx
	mov cx, i
	cmp cx, 0
	je postIter
	fld1
faqLoop:
	fdiv st(1), st(0)
	fld1
	faddp st(1), st(0)	; inc
	loop faqLoop
	faddp st(0), st(0)
	
postIter:
	fadd st(2), st(0)	; add SUM, TEMP
	fabs
	inc i
	
	push eax
	fcomp st(1)	; cmp TEMP, PREC
	fstsw ax
	fwait
	sahf
	pop eax
	ja nextIter
	
	mov cx, i
	mov rangeLength, cx
	faddp st(0), st(0)
	popa
	ret 12
SinSum endp

AddDouble proc doublePtr:dword, additionPtr:dword
	pusha
	mov eax, doublePtr
	mov ebx, additionPtr
	
	fld qword ptr [ebx]	; s(1) = addition
	fld qword ptr [eax]	; s(0) = doublePtr
	fadd st(0), st(1)
	
	fstp qword ptr [eax]
	faddp st(0), st(0)
	popa
	ret 4
AddDouble endp

work proc x:qword
	local xBuffer:qword
	pusha
	
	mov eax, dword ptr[x]
	mov dword ptr xBuffer, eax
	mov eax, dword ptr[x+4]
	mov dword ptr xBuffer+4, eax
	lea eax, a
	fld qword ptr [eax]
	lea eax, xBuffer
	fld qword ptr ss:[eax]
	faddp st(1), st(0)
	fstp qword ptr ss:[eax]
	
	; print argument
	invoke FloatToStr, xBuffer, offset strBuffer
	print addr wall
	print addr strBuffer
	print addr tab
	
	; print my function result
	invoke SinSum, addr x, offset a, offset prec
	lea eax, x
	fstp qword ptr [eax]
	invoke FloatToStr, x, offset strBuffer
	print addr wall
	print addr strBuffer
	print addr tab
	
	; print my range length
	;print addr wall
	;add rangeLength, '0'
	;print addr rangeLength
	;print addr tab
	
	; print c function result
	invoke crt_sin, xBuffer
	lea eax, xBuffer
	fstp qword ptr ss:[eax]
	invoke FloatToStr, ss:xBuffer, offset strBuffer
	print addr wall
	print addr strBuffer
	print addr tab
	print addr wall
	print addr endl
	
	popa
	ret 6
work endp

start:
	finit
	
	mov cx, 16
continueWork:
	invoke work, x1
	invoke AddDouble, offset x1, offset deltaX
	loop continueWork
	
    invoke ExitProcess, 0
end start
