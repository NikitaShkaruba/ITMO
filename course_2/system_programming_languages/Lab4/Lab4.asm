.186
; Variant 19
; Input 1.3.2
;  	From binary file. Read from the beginning. Parameter: fileName. 
; Output 2.2.4
; 	To a existing, previously flushed, text file.

stack segment para stack 'stack'
	db 100h dup(?)
stack ends
 
data segment para public 'data'
	source db 'dnnosrc'
	result dw ?
	binStr db 4 dup (?)
	
	sourceSize dw 0
	
	; fileSpec is: [diskname:]\filename\[.type].
	inPath db 'C:\input.bin', 0
	outPath db 'C:\out.txt', 0
	handle dw ?
	fileSize dw ?
data ends

code segment para public 'code'
assume cs:code, ds:data, ss:stack
extrn writeToTextFile : near
extrn wordToStr : near
extrn getBinaryInput : near
extrn strToWord : near

main:
	mov ax, data
	mov ds, ax
	
	; get input
	; void getBinaryInput(char* fileSpec, char* Handle, char* to, char* dataSize, );
	lea ax, sourceSize
	push ax
	lea ax, source
	push ax
	lea ax, handle
	push ax
	lea ax, inPath
	push ax
	call getBinaryInput
	cmp ax, 1
	je incorrect
	
	; convert
	; void strToWord(char* src, size_t srcSize, char* result);
	lea ax, result
	push ax
	mov ax, sourceSize
	push ax
	lea ax, source
	push ax
	call strToWord
	cmp ax, 1
	je incorrect
	
	; convert word to text representation
	; void wordToText(char* source, char* resiever)
	lea ax, binStr
	push ax
	lea ax, result
	push ax
	call wordToStr
	cmp ax, 1
	je incorrect
	
	; write
	; void writeToTextFile(char* filepath, char* handle, char* data, char dataSize);
	mov ax, 4 ; (!)
	push ax
	lea ax, binStr
	push ax
	lea ax, handle
	push ax
	lea ax, outPath
	push ax
	call writeToTextFile
	cmp ax, 1
	je incorrect
	
correct:
	mov ax, 4C00h
	int 21h

incorrect:	
	mov ax, 4C01h
	int 21h
code ends
end main
