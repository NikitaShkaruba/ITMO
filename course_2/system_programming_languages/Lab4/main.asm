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
	
	; fileSpec is: [имя диска:] имя файла [.тип файла].
	inPath db 'C:\input.bin', 0
	outPath db 'C:\out.txt', 0
	handle dw ?
	fileSize dw ?
	
	maxStrSize equ 6
data ends

code segment para public 'code'
assume cs:code, ds:data, ss:stack

; void wordToText(char* source, char* resiever)
wordToStr proc
	push dx
	push bx
	push bp
	push si
	mov bp, sp
	add bp, 8

	mov si, 0
	mov bx, [bp + 2]
	mov dx, [bx]
	mov bx, [bp + 4]
	
	; format [1234]
	; [1]
	mov al, dh
	shr ax, 4
	add al, '0'
	mov byte ptr [bx + si], al
	inc si
	; [2]
	mov al, dh
	shl al, 4
	shr al, 4
	add al, '0'
	mov byte ptr [bx + si], al
	inc si
	; [3]
	mov al, dl
	shr al, 4
	add al, '0'
	mov byte ptr [bx + si], al
	inc si
	; [4]
	mov al, dl
	shl al, 4
	shr al, 4
	add al, '0'
	mov byte ptr [bx + si], al
	
	pop si
	pop bp
	pop bx
	pop dx
	ret 4
wordToStr endp

;void getFileLength(Handle* handle, char* sizePtr)
getFileSize proc
	push bx
	push cx
	push dx
	push bp
	mov bp, sp
	add bp, 8
	
	; moving fileptr(!) to an end
	mov ah,  42h
	mov bx,  [bp + 2]   ;  FH -> bx
	mov bx, [bx]
	mov al,  2   	; смещение от конца файла
	xor cx,  cx
	xor dx,  dx  	; смещение  cx:dx = 0
	int 21h
	jc  IncorrectGetFileSize
	; move fileSize
	mov bx, [bp + 4]
	mov [bx],  ax
	
	; moving fileptr(!) to a beginning
	mov  ah, 42h
	mov bx, [bp + 2]   ;  FH -> bx
	mov bx, [bx]
	mov al, 0  ; смещение от начала файла
	xor cx, cx
	xor dx, dx
	int 21h
	jc IncorrectGetFileSize
	jmp CorrectGetFileSize
	
IncorrectGetFileSize:
	xor ax, ax
	inc ax
	jmp ExitGetFileSize
CorrectGetFileSize:
	xor ax, ax
	jmp ExitGetFileSize
	
ExitGetFileSize:
	pop bp
	pop dx
	pop cx
	pop bx
	ret 4
	
getFileSize endp

; void getBinaryInput(char* fileSpec, char* Handle, char* to, char* dataSize, );
getBinaryInput proc
	push bx
	push cx
	push dx
	push bp
	mov bp, sp
	add bp, 8
	
	; open
	mov ah, 3Dh 		; 32h - openFile
	mov al, 0h  		; 0 - read; 1 - write; 2 - readwrite;
	mov dx, [bp + 2] 	; dx get's the fileSpec
	int 21h
	jc IncorrectGetBinaryInput
	mov bx, [bp + 4]
	mov [bx], ax		; ax contains fieManipulator

	; gettingFileLength
	;void getFileLength(Handle* handle, char* to)
	mov ax, [bp + 8]	; sourceSize
	push ax
	mov ax, [bp + 4]	; local handle (!)
	push ax
	call getFileSize
	
	; read
	mov ah, 3Fh
	mov bx, [bp + 8]	; how much
	mov cx, [bx]		;
	mov dx, [bp + 6]	; to
	mov bx, [bp + 4]	; from spec
	mov bx, [bx]
	int 21h
	jc IncorrectGetBinaryInput
	mov bx, [bp + 8]
	mov [bx], cl

	; close
	mov ah, 3Eh
	mov bx, [bp + 4]
	mov bx, [bx]
	int 21h
	jc IncorrectGetBinaryInput
	jmp CorrectGetBinaryInput
	
CorrectGetBinaryInput:
	xor ax, ax
	jmp ExitGetBinaryInput
IncorrectGetBinaryInput:
	xor ax, ax
	inc ax
	jmp ExitGetBinaryInput
	
ExitGetBinaryInput:
	pop bp
	pop dx
	pop cx
	pop bx
	ret  8
getBinaryInput endp

; void writeToTextFile(char* filepath, char* handle, char* data, char dataSize);
writeToTextFile proc
	push bx
	push cx
	push dx
	push bp
	mov bp, sp
	add bp, 8
	
	; open
	mov ah, 3Dh 		; 32h - openFile
	mov al, 1h  		; 0 - read; 1 - write; 2 - readwrite;
	mov dx, [bp + 2] 	; dx get's the filepath
	int 21h
	jc IncorrectWriteToTextFile
	mov bx, [bp + 4]
	mov [bx], ax		; ax contains fieManipulator

	
	; write
	mov ah, 40h  		;функция записи в файл
	mov bx, [bp + 4]	; handle
	mov bx, [bx]		;
	mov cx, [bp + 8]  	; длина записи
	mov dx, [bp + 6] 	; адрес записи DS:DX 
	int 21h
	jc incorrectWriteToTextFile

	; close
	mov ah, 3Eh
	mov bx, [bp + 4]
	mov bx, [bx]
	int 21h
	jc IncorrectGetBinaryInput
	jmp CorrectGetBinaryInput
	
correctWriteToTextFile:
	xor ax, ax
	jmp ExitGetBinaryInput
incorrectWriteToTextFile:
	xor ax, ax
	inc ax
	jmp ExitWriteToTextFile
	
exitWriteToTextFile:
	pop bp
	pop dx
	pop cx
	pop bx
	ret  8
writeToTextFile endp

; void strToWord(char* src, size_t srcSize, char* result);
strToWord proc
	push bx
	push cx
	push dx
	push bp					; registers(8)
	
	mov bp, sp 				; bp now is pre-sp	
	add bp, 8				; bp now pre sp
	
	mov cx, [bp + 4]  	 	; sourseSize
	cmp cx, maxStrSize 		
	jg incorrectStrToWord
	mov bx, [bp + 2]		; source ptr
	
	xor ax, ax
procloop:					; ALL Together: result = (1)result*10 + (2)nextChar - (3)'0'
	mov dx, 10				;
	mul dx					; 1) result *=10
	cmp dx, 0				; dx contains not zero, if there's an overflow after mul
	jne incorrectStrToWord
	
	mov dl, byte ptr [bx] 	;
	cmp dl, '0'				;	my function
	jl incorrectStrToWord	;	handles only
	cmp dl, '7'				;	octal numbers
	jg incorrectStrToWord	;
	
	add al, dl 				; 2) result += nextChar
	jc incorrectStrToWord
	
	sub al, '0'				; 3) result -= '0'
	
	inc bx 					;
	loop procloop			;
	jmp correctStrToWord

incorrectStrToWord:
	mov ax, 1
	jmp exitStrToWord
correctStrToWord: 
	; sending result
	mov bx, [bp + 6]
	mov [bx], ax
	jmp exitStrToWord
		
exitStrToWord:
	pop bp
	pop dx
	pop cx
	pop bx
	ret 6
strToWord endp

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
	
	; convert
	; void strToWord(char* src, size_t srcSize, char* result);
	lea ax, result
	push ax
	mov ax, sourceSize
	push ax
	lea ax, source
	push ax
	call strToWord
	
	; convert word to text representation
	; void wordToText(char* source, char* resiever)
	lea ax, binStr
	push ax
	lea ax, result
	push ax
	call wordToStr
	
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
	
	mov ax, 4C00h
	int 21h
code ends
end main
