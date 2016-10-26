stack segment para stack 'stack'
	db 100h dup(?) 
stack ends
	 
data segment para public 'data'
	arr dd 3, -5, 7, 21, -3, 9, 0, 11, -14, 2, 13, -14, 32, 5 
	arrSize equ 001Ch
	result dd 14 dup(?) 
	resultSize db 0h
	
	lBound equ 4
	uBound equ 4*12
data ends

code segment para public 'code'
	assume cs:code, ds:data, ss:stack
start:	
	mov ax, data
	mov ds, ax

	mov di, 4 * 13
outterBegin:
	cmp di, 0	
	jle preDraft
	mov bx, 0	
	mov si, 4	
innerBegin:		
	cmp si, di   
	je outterEnd
	mov ax, arr[bx]
	cmp arr[si], ax
	jle innerEnd	
	mov bx, si
innerEnd:	
	add si, 4  
	jmp innerBegin
outterEnd:
	cmp arr[bx], 0
	jle preDraft
	mov ax, arr[bx]		;
	xor ax, arr[di]		;
	xor arr[di], ax		; xor swap
	xor ax, arr[di]  	; xor ax[0], [di]
	mov arr[bx], ax		;
	sub di, 4
	jmp outterBegin

preDraft:	
	mov si, 0
	mov di, 0
	mov cx, arrSize
	neg arr[lBound]
	inc arr[lBound]
	neg arr[uBound]
	inc arr[uBound]	
	mov ax, arr[lBound] 
	cmp ax, arr[uBound]	
	jle draft
	xor ax, arr[uBound]
	xor arr[uBound], ax
	xor ax, arr[uBound]
	mov arr[lBound], ax
draft:
	mov ax, arr[si]
	cmp ax, [lBound]
	jl nextN
	cmp ax, [uBound]
	jg nextN
	mov result[di], ax
	add di, 4
	inc resultSize	
nextN:	
	add si, 4
	loop draft
	
	mov ax, 4C00H
	int 21h	
code ends
end start
