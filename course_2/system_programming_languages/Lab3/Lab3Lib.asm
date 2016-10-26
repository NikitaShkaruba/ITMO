code segment para public 'code'
assume cs:code

; void strToWord(char* str, size_t size);
public strToWord
strToWord proc
prolog:
	push bx
	push cx
	push dx 	
	push bp
	
	mov bp, sp 				; bp now is pre-sp	
	mov bx, [bp + 12]  		; bx + registers(8) + retAddres(2) + sourceAddress(2) = sourceSizeAddress(2)
	mov cl, byte ptr [bx]
	cmp cl, 6 				; masStrSize
	jg incorrect
	mov bx, [bp + 10]		; bp + registers(8) + retAddres(2) = sourceAddress(2)
	
	xor ax, ax
procloop:					; ALL Together: result = (1)result*10 + (2)nextChar - (3)'0'
	mov dx, 10				;
	mul dx					; 1) result *=10
	cmp dx, 0				; dx contains not zero, if there's an overflow after mul
	jne incorrect
	
	mov dl, byte ptr [bx] 	;	
	cmp dl, '0'				;	my function
	jl incorrect			;	handles only
	cmp dl, '7'				;	octal numbers
	jg incorrect			;
	
	add al, dl 				; 2) result += nextChar
	sub al, '0'				; 3) result -= '0'
	inc bx 					;
	loop procloop			;
	
	jmp correct

incorrect:
	mov ax, 1
	jmp epilog
correct: 
	mov ax, 0
	jmp epilog
	
epilog:
	pop bp
	pop dx
	pop cx
	pop bx
	ret 4
strToWord endp
code ends
end
