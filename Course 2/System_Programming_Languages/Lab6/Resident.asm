; Variant 15
; Interrupt - 09h - keyboard.
; <Alt>+<Q> - switch dispay to a new video-page, where  belongs some picture
; <Alt>+<X> - uninstall program from memory

; consts
VPage1 equ 0B900h
scancode_q equ 10h
scancode_x equ 2dh
altPressedBits equ 00000100b
screenSize equ 80*25 ; every symbol is 2 bytes {ASCII code , attribute}



code segment para public 'code'
assume cs:code, ds:code, ss:code
org 100h ; offset memory for psp
	; data
	Picture dw screenSize dup(1515h) 

begin:
	jmp setup

	; data segment
	installMessage db 'Program has been set in memory. For switch use: "ctrl+q". For uninstall - "ctrl+x"', '$'
	omitInstallMessage db 'Program is already installed. For switch use: "ctrl+q". For uninstall - "ctrl+x"', '$'
	uninstallMessage db 'Program has been removed from memory', '$'
	isCovered db 0h
	systemHandler dd ?	; stores system handler adress
	
; resident one
switch_handler proc
	push ax
	push cx
	push ds
	push es
	
	; switch 
	cmp isCovered, 0h
	je setPictureCase
	jne restoreScreenCase
	
setPictureCase:
	; is ctrl pressed?
	mov ah, 02h
	int 16h
	and al, altPressedBits
	cmp al, 0h
	je invokeSystemInterrupt
	; is p or q pressed too?
	in al, 60h 
	cmp al, scancode_x
	je uninstall
	cmp al, scancode_q
	jne invokeSystemInterrupt
	; if survived
	mov isCovered, 1h
	mov ah, 05h
	mov al, 1h	; al - page number
	int 10h
	jmp omitSystemInterrupt
	
restoreScreenCase:
	; is ctrl pressed?
	mov ah, 02h
	int 16h
	and al, altPressedBits
	cmp al, 0h
	je invokeSystemInterrupt
	; is q pressed?
	in al, 60h 
	cmp al, scancode_q
	jne omitSystemInterrupt
	; if survived
	mov isCovered, 0h
	mov ah, 05h
	mov al, 0h	; al - page number
	int 10h
	jmp omitSystemInterrupt

uninstall:
	; setting old handler into int.table
	mov ax, word ptr cs:systemHandler[2]
	mov ds, ax
	mov dx, word ptr cs:systemHandler
	mov ax, 2509h
	int 21h

	; set already-isntalled flag
	mov ax, 25FFh
	mov dx, 0000h
	int 21h
	
	push es
	; free encironment area (PSP) 
	mov es, cs:2Ch
	mov ah, 49h
	int 21h
	; free resient itself
	push cs
	pop es
	mov ah, 49h
	int 21h
	;
	pop es
	
	; print message
	push ds
	mov ax, cs
	mov ds, ax
	lea dx, cs:uninstallMessage
	mov ah, 9h
	int 21h
	pop ds
	
	jmp omitSystemInterrupt
	
invokeSystemInterrupt:
	pushf
	call cs:systemHandler
	jmp exit
	
omitSystemInterrupt:
	in al, 61H  	; get value of keyboard control lines
    mov ah, al      ; save it
    or al, 80h      ; set the "enable kbd" bit
    out 61H, al     ; and write it out the control port
    xchg ah, al     ; fetch the original control port value
    out 61H, al     ; and write it back
    
    mov al, 20H     ; send End-Of-Interrupt signal
    out 20H, al     ; to the 8259 Interrupt Controller	
	
	jmp exit
	
exit:
	pop es
	pop ds
	pop cx
	pop ax
	
	iret
switch_handler endp
switch_handler_end:

; prepares everything
setup: 
	; getting FF interrut vector
	mov ax, 35FFh
	int 21h
	cmp bx, 0000h
	je install
	jne omitInstall
	
install:
	; filling page 1
	mov ax, cs
	mov ds, ax
	lea si, Picture
	mov ax, VPage1
	mov es, ax
	mov di, 0h
	mov cx, screenSize
	rep movsw
	
	; set already-isntalled flag
	mov ax, 25FFh
	mov dx, 0001h
	int 21h
	
	;print message
	mov ax, cs
	mov ds, ax
	lea dx, installMessage
	mov ah, 9h
	int 21h
	
	; getting system int adress
	mov ax, 3509h
	int 21h
	mov word ptr cs:systemHandler, bx 		; systemHandler is double-word
	mov word ptr cs:systemHandler+2, es
	
	; setting our handler to interrupt table
	mov ax, 2509h
	lea dx, switch_handler
	int 21h

	; saving resident handler([dx] - how much paragraph's) in memory 
	lea dx, switch_handler
 	sub dx, offset switch_handler_end
	mov cl, 4
	shr dx, cl
	inc dx 			; dx == 0 - rare case
	mov ax, 3100h
	int 21h	

omitInstall:
	;print message
	mov ax, cs
	mov ds, ax
	lea dx, omitInstallMessage
	mov ah, 9h
	int 21h
	
	; save exit
	mov ax, 4C00h
	int 21h
;stack segment
localStack dw 100h dup(?)
code ends
end begin
