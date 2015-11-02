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

.stack 100h

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
	testResult dd ?
	firstX dd ?
	deltaX dd ?
	lastX dd ?
	paramA dd ?
	precision dd ?
	floatBuffer db 100 ?
	
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
computeFunction proc x:dword, a:dword, prec:dword
	local i:byte
	
	push cx
	mov i, 0
	fldz	; sum
	fldz  ; temp
	
	.repeat
	fst st(0) ; remove temp
	fld1	; temp = 1
	
	lea eax, i
	mov cl, [eax]
powMark:
	fmul x 		; temp *= x^i
	loop powMark
	
	fadd st(1), st(0)
	fst st(0)
	
	fldpi		; st(0) = pi
	fild i 	
	fmul 		; st(0) = pi*i 
	mov dx, 2
	fild dx	 
	fdiv		; st(0) = pi*i/2
	fadd paramA ; st(0) = pi*i/2 + a
	fsin 		; st(0) = sin(pi*i/2 + a)
	fmulp  		; temp *= sin(a + i*Pi/2) 
	
	lea eax, i
	mov cl, [eax]
faqMark:
	fdiv cx	; temp /= i!
	loop faqMark
	
	fadd st(1), st(0)	; sum += temp
	inc i	
	.until st(0) > prec
	
	fst st(0)	; remove temp
	pop cx
	ret		; i do not need to pop locals, hehe
computeFunction endp


computeFunctionTest proc
	pushad

	invoke computeFunction, testX, testA, testPrec
	fst testResult
	
	popad
	ret
computeFunctionTest endp

getUserData proc
	invoke StdOut, addr startMessage
    invoke StdOut, addr funcMessage
	
	invoke StdOut, addr getXmessage
	invoke StdIn, addr floatBuffer, 100
	invoke StrToFloat, addr floatBuffer, addr firstX
	
	invoke StdOut, addr getDXmessage
	invoke StdIn, addr floatBuffer, 100
	invoke StrToFloat, addr floatBuffer, addr deltaX
	
	invoke StdOut, addr getFXMessage
	invoke StdIn, addr floatBuffer, 100
	invoke StrToFloat, addr floatBuffer, addr lastX
	
	invoke StdOut, addr getAMessage
	invoke StdIn, addr floatBuffer, 100
	invoke StrToFloat, addr floatBuffer, addr paramA
	
	invoke StdOut, addr getPrecisionMessage
	invoke StdIn, addr floatBuffer, 100
	invoke StrToFloat, addr floatBuffer, addr precision
	
	ret
getUserData endp


start:
	call computeFunctionTest
	call getUserData
	
	;invoke computeFunction, startX, a, precision
	;invoke FloatToStr, result, floatBuffer
	;invoke StdOut, addr floatBuffer
	
    invoke ExitProcess, 0
end start
