stack segment para stack 'stack'
	db 100h dup(?)
stack ends
 
data segment para public 'data'
	source db '12A'
	sourceSize db 3
data ends

code segment para public 'code'
assume cs:code, ds:data, ss:stack
extrn strToWord:near

main:
	mov ax, data
	mov ds, ax
	
	lea ax, sourceSize
	push ax
	lea ax, source
	push ax
	call strToWord
	
	mov ax, 4C00h
	int 21h
code ends
end main
