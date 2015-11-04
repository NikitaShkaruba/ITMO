.386					; Enable 80386+ instruction set
.model flat, stdcall	; Flat, 32-bit memory model (not used in 64-bit)
option casemap: none	; Case sensitive syntax

; MASM32 proto types for Win32 functions and structures
include c:\masm32\include\windows.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\masm32.inc
include \masm32\macros\macros.asm
; MASM32 object libraries
includelib c:\masm32\lib\kernel32.lib
includelib c:\masm32\lib\masm32.lib
; C function
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.stack 100h

.data
	startMessage db "System Programming Languages, final Lab 7. Made by Shkaruba Nikita, group P3218", 13, 10, 0
	funcMessage db "My func is:  sin(x + a)", 13, 10, 0
	tableMessage db 13, 10, 10, "Resulted table: ", 13, 10, " |(x+a)", 9, " | my result", 9, " | c result", 9, " |series length", 9, " |", 13 , 10, 0
	getXmessage db "Input first x: ", 0			; first x 
	getDXmessage db "Input delta x: ", 0		; delta x
	getFXMessage db "Input last x: ", 0			; last x
	getAMessage db "Input a: ", 0				
	getPrecisionMessage db "Input Precision: ", 0
	
	inFormat db "%lf", 0
	outFormat db "%d", 0
	endl db 10, 8, 0
	tab db 9, 0
	wall db ' ', '|', ' ', 0
.data?
	x1 dq ?
	deltaX dq ?
	x2 dq ?
	a dq ?
	prec dq ?
	strBuffer db 20 dup(?)
	rangeLength dd ?
	
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
	
	xor ecx, ecx
	mov cx, i
	mov rangeLength, ecx
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
		
	; print c function result
	invoke crt_sin, xBuffer
	lea eax, xBuffer
	fstp qword ptr ss:[eax]
	invoke FloatToStr, ss:xBuffer, offset strBuffer
	print addr wall
	print addr strBuffer
	print addr tab
	
	; print my range length
	print addr wall
	invoke crt_printf, addr outFormat, rangeLength
	print addr tab
	print addr tab
	print addr wall
	print addr endl
	
	popa
	ret 6
work endp

getUserData proc
	print addr startMessage
    print addr funcMessage
	
	print addr getXmessage
	invoke crt_scanf, addr inFormat, addr x1
	
	print addr getDXmessage
	invoke crt_scanf, addr inFormat, addr deltaX
	
	print addr getFXMessage
	invoke crt_scanf, addr inFormat, addr x2
	
	print addr getAMessage
	invoke crt_scanf, addr inFormat, addr a
	
	print addr getPrecisionMessage
	invoke crt_scanf, addr inFormat, addr prec
	
	print addr tableMessage
	
	ret
getUserData endp

start:
	finit
	call getUserData
	
	xor ecx, ecx
	mov cx, 16
continueWork:
	invoke work, x1
	invoke AddDouble, offset x1, offset deltaX
	
	push ax
	fld x1
	fcomp x2
	fstsw ax
	fwait
	sahf
	pop ax
	jb continueWork
	
    invoke ExitProcess, 0
end start
