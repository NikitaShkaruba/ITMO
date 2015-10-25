; Hypotetic processor's word - 19 bit
; Macroses:
;	1. read element by index from word array
;	2. write element by index to word array
; 	3. word's addition
; Work:
; 	- To every negative add max positive element
; 	- To every positive ann min negative element
.186

; 16 words * 19 bit in word == 19 words * 16 bit in word
loadW macro arr, i
local LoadAddition, Acase0_4, Acase10, Acase11_15, Acase5, Acase6_9, PostLoadAddition, LoadPrimary, Pcase0_4, Pcase5_9, Pcase10_15, PostLoadPrimary, testZ, setZFlag, clearZFlag, testN, setNFlag, clearNFlag, exit 
	push bx
	push cx
	
LoadPrimary:
	cmp i, 4
	jle Pcase0_4
	cmp i, 9
	jle Pcase5_9
	jg Pcase10_15
	
Pcase0_4:
	; {3 + 3(i)} is an amount of bits in the left real word
	; rol ax, 3 + 3*(i) 
	shl i, 1
	mov ax, arr[i]
	shr i, 1
	mov cx, i
	mul cx, 3
	add cx, 3
	shl ax, cl
	
	; shr bx, 16 - 3 - 3*(i)
	inc i
	shl i, 1
	mov bx, arr[i]
	shr i, 1
	dec i
	mov cx, i
	mul cx, 3
	neg cx
	add cx, 13
	shr bx, cl
	
	; concatinate
	or ax, bx
	jmp PostLoadPrimary
Pcase5_9:
	; {2 + 3*(i - 5)} is an amount of bits in the left real word
	; rol ax, 2 + 3*(i - 5) 
	inc i
	shl i, 1
	mov ax, arr[i]
	shr i, 1
	dec i
	mov cx, i
	sub cx, 5
	mul cx, 3
	add cx, 2
	shl ax, cl
	
	; shr bx, 16 - 2 - 3*(i - 5)
	add i, 2
	shl i, 1
	mov bx, arr[i]
	shr i, 1
	sub i, 2
	mov cx, i
	sub cx, 5
	mul cx, 3
	neg cx
	add cx, 14
	shr bx, cl
	
	; concatinate
	or ax, bx
	jmp PostLoadPrimary
Pcase10_15:
	; {1 + 3*(i - 10)} is an amount of bits in the left real word
	; rol ax, 1 + 3*(i - 10) 
	add i, 2
	shl i, 1
	mov ax, arr[i]
	shr i, 1
	sub i, 2
	mov cx, i
	sub cx, 10
	mul cx, 3
	inc cx
	shl ax, cl
	
	; shr bx, 16 - 1 - 3*(i - 10) 
	add i, 3
	shl i, 1
	mov bx, arr[i]
	shr i, 1
	sub i, 3
	mov cx, i
	sub cx, 10
	mul cx, 3
	neg cx
	add cx, 15
	shr bx, cl
	
	; concatinate
	or ax, bx
	jmp PostLoadPrimary
PostLoadPrimary:

	; 1.load addition to dx
LoadAddition:
	cmp i, 5
	jl Acase0_4
	je Acase5
	cmp i, 10
	jl Acase6_9
	je Acase10
	jmp Acase11_15
		
Acase0_4:
	shl i, 1
	mov dx, arr[i]
	
	;rol dx, 3 + (i)
	shr i, 1
	mov cx, i
	inc cx
	mul cx, 3
	rol dx, cl
	jmp postLoadAddition

Acase5:
	shl i, 1
	mov dx, arr[i]
	
	and dx, 01h ; clear other bytes
	add i, 2
	mov bx, arr[i]
	and bx, 0C000h
	or dx, bx
	rol dx, 2
	sub i, 2
	shr i, 1
	jmp postLoadAddition
	
Acase6_9:
	inc i
	shl i, 1
	mov dx, arr[i]
	
	; rol dx, 5 + 3*(i - 6) ; 
	shr i, 1
	dec i
	mov cx, i
	sub cx, 6
	mul cx, 3
	add cx, 5
	rol dx, cl
	jmp postLoadAddition

Acase10:
	inc i
	shl i, 1
	mov dx, arr[i]
	
	and dx, 0003h ; clear other bytes
	add i, 2
	mov bx, arr[i]
	and bx, 8000h
	or dx, bx
	rol dx, 1
	sub i, 2
	shr i, 1
	dec i
	jmp postLoadAddition
	
Acase11_15:
	add i, 2
	shl i, 1
	mov dx, arr[i]
	
	; rol dx, 4 + 3*(i - 11)
	shr i, 1
	sub i, 2
	mov cx, i
	sub cx, 11
	mul cx, 3
	add cx, 4
	rol dx, cl
	jmp postLoadAddition

PostLoadAddition:
	; set all the flags
	and dx, 0007h ; coz my addition is the last 3 bits
	jmp testZ
	
testZ:
	cmp dl, 0
	jne clearZFlag
	cmp ax, 0
	jne clearZFlag
	je setZFlag
setZFlag:
	or dl, 1h
	jmp testN
clearZFlag:
	and dl, 0EFh
	jmp testN
	
testN:
	test dl, 04h
	je setNFlag
	jne clearNFlag
setNFlag:
	or dl, 20h
	jmp exit
clearNFlag:
	and dl, 0DFh
	jmp exit

exit:
	pop cx
	pop bx
endm

; 2.
writeW macro eReg, arr, idx
endm

; 3.
addW macro reg1, reg2
	
endm

stack segment para stack 'stack'
	db 100h dup(?)
stack ends

	arrSize equ 19
data segment para public 'data'
	array dw arrSize dup(0F0F0h)
	min dd ?
	max dd ?
data ends

code segment para public 'code'
assume cs:code, ds:data, ss:stack

loadWTest proc
	mov si, 0	; case0_4 addition, _4 primary
	loadW array, si	
	
	mov si, 5	; case5
	loadW array, si	
	
	mov si, 7	; case6_9
	loadW array, si	
	
	mov si, 10	; case10
	loadW array, si	
	
	mov si, 12	; case11_15
	loadW array, si
	
	ret
loadWTest endp

axTest proc
	
axTest endp

main:
	mov ax, data
	mov ds, ax
	
	;call dxTest
	call loadWTest
	;call Fulltest
	
	mov ax, 4C00h
	int 21h
code ends
end main
