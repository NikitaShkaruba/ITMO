.model small
.stack 128

.data
	primary db 'ATGOYRBDK9XUF4$KBSNC0W9YTRMCTVC8M1SVZXAY0RLI77S735WVUKAYNT7ZD3YI'
	primarySize equ 64
	
	lBound db '0'
	uBound db  '9'
	dallar db '$'
	cloak dw 0aaaah, 0bbbbh, 0cccch, 0ddddh

.code

; void newLine();
newLine proc
	mov dl, 0ah
	mov ah, 02h
	int 21h
	mov dl, 0dh
	mov ah, 02h
	int 21h
	ret
newLine endp

;void PrintPrimaryString();
PrintPrimaryString proc
	mov cx, primarySize
	lea si, primary
NextChar:
	lodsb
	mov dl, al
	mov ah, 02h
	int 21h
	loop NextChar
	
	call newLine
	ret
PrintPrimaryString endp

PrintParsedString1 proc
	mov cx, primarySize
	lea si, primary
	mov di, 0 ; cloak pointer
	mov bx, cloak[di]
Parsed1Loop:
	lodsb
	rcl bx, 1
	jc incorrect
	cmp al, lBound
	jl correct	
	cmp al, uBound
	jle incorrect
correct:	
	mov dl, al
	mov ah, 02h
	int 21h
incorrect:
	cmp cx, 48
	je loadCloak
	cmp cx, 32
	je loadCloak
	cmp cx, 16
	je loadCloak
	loop Parsed1Loop
	
	call newline
	ret
	
loadCloak:				;(
	add di, 8
	mov bx, cloak[di]
	loop Parsed1Loop
PrintParsedString1 endp

PrintParsedString2 proc
	std
	mov cx, primarySize
	dec si ;si is almost improperant after PrintParsedString1
Parsed2Loop:
	lodsb
	
	jnc isDallar
isNumber:
	cmp al, lBound
	jl isDallar			
	cmp al, uBound
	jg isDallar
	jmp exit
isDallar:
	clc	
	cmp al, dallar  ; i store information about last symbol 
	jne correct2 	; in carry flag. If it's dallar 
	stc 			; then c==1
correct2:
	mov dl, al
	mov ah, 02h
	int 21h
	loop Parsed2Loop

exit:
	call newLine
	ret
PrintParsedString2 endp

main:
	mov ax, @data
	mov ds, ax
	
	call PrintPrimaryString
	call PrintParsedString1
	call PrintParsedString2
	
	mov ax, 4C00h
	int 21h
end main
	