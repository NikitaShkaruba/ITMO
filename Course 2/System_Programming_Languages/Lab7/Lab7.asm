.386					; Enable 80386+ instruction set
.model flat, stdcall	; Flat, 32-bit memory model (not used in 64-bit)
option casemap: none	; Case sensitive syntax

; *************************************************************************
; MASM32 proto types for Win32 functions and structures
; *************************************************************************  
include c:\masm32\include\windows.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\masm32.inc
include c:\masm32\include\libc.inc

; *************************************************************************
; MASM32 object libraries
; *************************************************************************  
includelib c:\masm32\lib\kernel32.lib
includelib c:\masm32\lib\masm32.lib
includelib c:\masm32\lib\libc.lib

.data
	startMessage db "System Programming Languages, final Lab 7. Made by Shkaruba Nikita, group P3218", 13, 10, 0
	funcMessage db "My func is:  sin(x + a)", 13, 10, 0
	
	getXmessage db "Input first x: ", 0			; first x 
	getDXmessage db "Input delta x: ", 0		; delta x
	getFXMessage db "Input last x: ", 0			; last x
	getAMessage db "Input a: ", 0				
	getPrecisionMessage db "Input Precision: ", 0
	
	testX dd 1.8000
	testA dd 1.6000
	testPrec dd 0.001
.data?
	firstX dq 1 dup(?)
	deltaX dq 1 dup(?)
	lastX dq 1 dup(?)
	a dq 1 dup(?)
	precision dq 1 dup(?)
	
.code
;	double computeFunction(double x, double a, double precision) {
;		sum s = 0;
;		int i;		
;		float temp;
;
;		do {
;			temp = pox(x, i);
;			temp *= sin(a + i*Pi/2);
;			temp /= fac(i);
;
;			sum += temp;
;		} while(temp > precision);
;		
;		return sum;
;}
computeFunction proc x:dword, a:dword, precision:dword
	pushad
	local temp:dword
	
	.repeat
	fld x
	
	.until st(0) > precision
	
	
	popad
	ret
computeFunction endp


computeFunctionTest proc
	pushad

	invoke computeFunction, testX, testA, testPrec
	
	popad
	ret
computeFunctionTest endp
start:
	mov eax, 00FFh
	xor ax, ax
	
	call computeFunctionTest
	
	mov eax, 00FFh
	xor ax, ax
	
	;invoke StdOut, addr startMessage
    ;invoke StdOut, addr funcMessage
	
	;invoke StdOut, addr getXmessage
	;invoke StdIn, addr floatBuffer, 100
	;invoke StrToFloat, floatBuffer, addr firstx
	
	;invoke StdOut, addr getDXmessage
	;invoke StdIn, addr deltaX, 100
	
	;invoke StdOut, addr getFXMessage
	;invoke StdIn, addr lastX, 100	
	
	;invoke StdOut, addr getAMessage
	;invoke StdIn, addr a, 100
	
	;invoke StdOut, addr getPrecisionMessage
	;invoke StdIn, addr precision, 100
	
	
	;invoke computeFunction, startX, a, precision
	;invoke FloatToStr, result, floatBuffer
	;invoke StdOut, addr floatBuffer
	
    invoke ExitProcess, 0
end start
