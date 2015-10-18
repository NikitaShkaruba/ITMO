; Variant 15
; Interrupt - 09h - keyboard.
; When there's a <Alt>+<Q>, switch dispay to a new
; video-page, where  belongs some picture

; consts
VPage1 equ 0B900h
screenSize equ 80*25 ; every symbol is 2 bytes {ASCII code , attribute}
scancode_q equ 10h
altPressedBits equ 00000100b


code segment para public 'code'
assume cs:code, ds:code, ss:code
org 100h ; offset memory for psp
	; data
	Picture dw screenSize dup(1515h) 

begin:
	jmp setup

	; data segment
	installMessage db 'Setting program in memory', '$'
	omitInstallMessage db 'program already installed', '$'
	isCovered db 0
	systemHandler dd ?	; stores system handler adress
	screenSize equ 80*25 ; every symbol is 2 bytes {ASCII code , attribute}
	customPicture db screenSize dup(15h) 
	
; resident one
switch_handler proc
	push ax
	push cx
	push ds
	push es
	push si
	push di
	
	; switch 
	cmp isCovered, 0
	je setPictureCase
	jne restoreScreenCase
	
setPictureCase:
	; is alt pressed?
	mov ah, 02h
	int 16h
	and al, altPressedBits
	cmp al, 0
	je invokeSystemInterrupt
	; is p pressed too?
	in al, 60h 
	cmp al, scancode_q
	jne invokeSystemInterrupt
	; if survived
	mov isCovered, 1
	mov ah, 05h
	mov al, 1	; al - page number
	int 10h
	jmp omitSystemInterrupt
	
restoreScreenCase:
	; is p pressed too?
	in al, 60h 
	cmp al, scancode_q
	jne omitSystemInterrupt
	; if survived
	mov isCovered, 0
	mov ah, 05h
	mov al, 0	; al - page number
	int 10h
	jmp omitSystemInterrupt
	
omitSystemInterrupt:
	in      al,61H             ;get value of keyboard control lines
    mov     ah,al              ; save it
    or      al,80h             ;set the "enable kbd" bit
    out     61H,al             ; and write it out the control port
    xchg    ah,al              ;fetch the original control port value
    out     61H,al             ; and write it back
    
    mov     al,20H             ;send End-Of-Interrupt signal
    out     20H,al             ; to the 8259 Interrupt Controller	
	
	jmp exit
	
invokeSystemInterrupt:
	pushf
	call cs:systemHandler
	jmp exit
	
exit:
	pop di
	pop si
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
	mov si, offset Picture
	mov ax, VPage1
	mov es, ax
	mov di, 0h
	mov cx, screenSize
	rep movsw
	
	; set already-isntalled flag
	mov ax, 25FFh
	mov dx, 0001h
	int 21h
	
	;print installMessage
	mov ax, cs
	mov ds, ax
	lea dx, installMessage
	mov ah, 9
	int 21h
	
	; getting system int adress
	mov ax, 3509h
	int 21h
	mov word ptr systemHandler, bx 		; systemHandler is double-word
	mov word ptr systemHandler+2, es
	
	; setting our handler into int.table
	mov ax, 2509h
	lea dx, switch_handler
	int 21h

	; saving resident handler([dx] cells) in memory 
	lea dx, switch_handler
 	sub dx, offset switch_handler_end
	mov cl, 4
	shr dx, cl
	inc dx 			; dx == 0 - rare case
	mov ax, 3100h
	int 21h	

omitInstall:
	;print uninstallMessage
	mov ax, cs
	mov ds, ax
	lea dx, omitInstallMessage
	mov ah, 9
	int 21h
	
	
	; save exit
	mov ax, 4C00h
	int 21h
;stack segment
localStack dw 100h dup(?)
code ends
end begin
