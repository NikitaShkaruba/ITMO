.186
code segment para public 'code'
assume cs:code
maxStrSize equ 6

; void wordToText(char* source, char* resiever)
; i am so sorry for this unrefactored procedure
public wordToStr	
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
	
	mov ax, 0
	pop si
	pop bp
	pop bx
	pop dx
	ret 4
wordToStr endp

;void getFileLength(Handle* handle, char* sizePtr)
public getFileSize 
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
	mov al,  2   	; offset from an end
	xor cx,  cx
	xor dx,  dx  	; offset  cx:dx = 0
	int 21h
	jc  IncorrectGetFileSize
	; move fileSize
	mov bx, [bp + 4]
	mov [bx],  ax
	
	; moving fileptr(!) to a beginning
	mov  ah, 42h
	mov bx, [bp + 2]   ;  FH -> bx
	mov bx, [bx]
	mov al, 0  ; offset from a beggining
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
public getBinaryInput
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
public writeToTextFile
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
	mov ah, 40h  		;
	mov bx, [bp + 4]	; handle
	mov bx, [bx]		;
	mov cx, [bp + 8]  	; length
	mov dx, [bp + 6] 	; adress DS:DX 
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
public strToWord
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
	mov ax, 0
	jmp exitStrToWord
		
exitStrToWord:
	pop bp
	pop dx
	pop cx
	pop bx
	ret 6
strToWord endp
code ends
end
