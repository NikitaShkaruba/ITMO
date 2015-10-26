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
local LoadAddition, Acase0_4, Acase10, Acase11_15, Acase5, Acase6_9, PostLoadAddition, LoadPrimary, Pcase0_4, Pcase5_9, Pcase10_15, PostLoadPrimary 
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
	; shl ax, 3 + 3*(i) 
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
	jmp PostLoadAddition

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
	jmp PostLoadAddition
	
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
	jmp PostLoadAddition

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
	jmp PostLoadAddition
	
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
	jmp PostLoadAddition

PostLoadAddition:
	; set all the flags
	and dx, 0007h ; coz my addition is the last 3 bits
	
	pop cx
	pop bx
endm

; 2.
writeW macro arr, i
local case0_4, case5, case6_9, case10, case11_15, exit
	pusha
	
case0_4:
	; 3*i - bit's before
	; 3 + 3*(i) - bit's after
	
	; clear past bytes, save others
	shl i, 1
	mov bx, arr[i]
	shr i, 1
	
	mov cx, i 	;shr bx, 16 - 3*i
	mul cx, 3
	neg cx
	add cx, 16
	shr bx, cl
	; load addition
	push dx
	shl bx, 3
	and dl, 07h
	add bl, dl
	pop dx
	; load primary first part
	push ax
	sub cx, 3
	shl bx, cl	;shl bx, 16 - 3 - 3*i 
	mov cx, i
	mul cx, 3
	add cx, 3
	shr ax, cl 	; shr ax, 3 + 3*i
	add bx, ax
	
	shl i, 1
	mov arr[i], bx
	shr i, 1
	pop ax
	; load primary second part
	push ax
	inc i
	shl i, 1
	mov bx, arr[i]
	shr i, 1
	dec i
	
	shl bx, cl	;shl bx, 3 + 3*i
	neg cx		
	add cx, 16
	shl ax, cl	;shl ax, 16 - 3 - 3*(i)
	shr ax, cl	;shr ax, 16 - 3 - 3*(i)
	add bx, ax
	mov cx, i
	mul cx, 3
	add cx, 3
	ror bx, cl	;ror bx, 3 + 3*i
	
	shl i, 1
	add i, 2
	mov arr[i], bx
	sub i, 2
	shr i, 1
	pop ax

	jmp exit
case5:
	shl i, 1	; i == 5
	mov bx, arr[i]
	shr i, 1
	
	push dx
	and bx, 0FFFEh
	shr dl, 2
	add bx, dx
	shl i, 1
	mov arr[i], bx
	shr i, 1
	pop dx
	
	inc i		; i == 6
	shl i, 1
	mov bx, arr[i]
	; load addition
	xor bx, bx
	and dl, 03h
	add bl, dl
	ror bx, 2
	; load primary first part
	push ax
	shr ax, 2
	add bx, ax

	mov arr[i], bx
	shr i, 1
	dec i
	pop ax
	
	; load primary last 2 bits
	add i, 2		; i == 7
	shl i, 1
	mov bx, arr[i]
	
	push ax
	mov cx, 2
	shl bx, 2
	and ax, 0003h
	add bx, ax
	
	ror bx, 2
	mov arr[i], bx
	shr i, 1
	sub i, 2
	pop ax
	
	jmp exit
case6_9:
	; 2 + 3*(i - 6) - bit's before
	; 5 + 3*(i - 6) - bit's after
	
	; clear past bytes, save others
	inc i
	shl i, 1
	mov bx, arr[i]
	shr i, 1
	dec i
	
	mov cx, i 	;shr bx, 16 - 2 - 3*(i - 6)
	sub cx, 6
	mul cx, 3
	neg cx
	add cx, 14
	shr bx, cl
	; load addition
	push dx
	shl bx, 3
	and dl, 07h
	add bl, dl
	pop dx
	; load primary first part
	push ax
	sub cx, 3
	shl bx, cl	;shl bx, 16 - 2 - 3*(i - 6)
	mov cx, i
	sub cx, 6
	mul cx, 3
	add cx, 5
	shr ax, cl 	; shr ax, 5 + 3*(i - 6)
	add bx, ax
	inc i
	
	shl i, 1
	mov arr[i], bx
	shr i, 1
	dec i
	pop ax
	; load primary second part
	push ax
	add i, 2
	shl i, 1
	mov bx, arr[i]
	shr i, 1
	sub i, 2
	
	shl bx, cl	;shl bx, bit's after. cl is proper from last cl's calls
	neg cx
	add cx, 16
	shl ax, cl	;shl ax, 16 - 3 - 3*(i)
	shr ax, cl	;shr ax, 16 - 3 - 3*(i)
	add bx, ax
	mov cx, i
	sub cx, 6
	mul cx, 3
	add cx, 5
	ror bx, cl	;ror bx, 5 + 3*(i - 6) - bit's after
	
	add i, 2
	shl i, 2
	mov arr[i], bx
	shr i, 1
	sub i, 2
	pop ax

	jmp exit
case10:
	inc i
	shl i, 1	
	mov bx, arr[i] ; i == 10
		
	push dx
	and bx, 0FFFCh ; clear last bytes
	shr dl, 1
	add bx, dx
	
	mov arr[i], bx
	shr i, 1
	dec i
	pop dx
	
	add i, 2		; i == 6
	shl i, 1
	mov bx, arr[i]
	
	; load addition
	xor bx, bx
	and dl, 1h
	add bl, dl
	ror bx, 1
	; load primary first part
	push ax
	mov cx, 1 
	shr ax, cl 
	add bx, ax

	mov arr[i], bx
	shr i, 1
	sub i, 2
	pop ax
	
	; load primary last bit
	add i, 3		; i == 7
	shl i, 1
	mov bx, arr[i]
	
	push ax
	shl bx, 1
	and ax, 0001h
	add bx, ax
	ror bx, 1
	
	mov arr[i], bx
	shr i, 1
	sub i, 3
	pop ax
	
	jmp exit
case11_15:
	; 2 + 3*(i - 6) - bit's before
	; 5 + 3*(i - 6) - bit's after
	; 1 + 3*(i - 11) - bit's before
	; 4 + 3*(i - 11) - bit's after
	
	; clear past bytes, save others
	inc i
	shl i, 1
	mov bx, arr[i]
	shr i, 1
	dec i
	
	mov cx, i 
	sub cx, 11
	mul cx, 3
	neg cx
	add cx, 15
	shr bx, cl	;shr bx, 16 - 1 - 3*(i - 11)
	; load addition
	push dx
	shl bx, 3
	and dl, 07h
	add bl, dl
	pop dx
	; load primary first part
	push ax
	sub cx, 3
	shl bx, cl	;shl bx, 16 - 2 - 3 - 3*(i - 6)
	mov cx, i
	sub cx, 11
	mul cx, 3
	add cx, 4
	shr ax, cl 	; shr ax, 4 + 3*(i - 11)
	add bx, ax
	inc i
	
	shl i, 1
	mov arr[i], bx
	shr i, 1
	dec i
	pop ax
	; load primary second part
	push ax
	add i, 2
	shl i, 1
	mov bx, arr[i]
	shr i, 1
	sub i, 2
	
	shl bx, cl	;shl bx, bit's after. cl is proper from last cl's calls
	neg cx
	add cx, 16
	shl ax, cl	;shl ax, 16 - 4 - 3*(i - 11)
	shr ax, cl	;shr ax, 16 - 4 - 3*(i - 11)
	add bx, ax
	mov cx, i
	sub cx, 11
	mul cx, 3
	add cx, 4
	ror bx, cl	;ror bx, 4 + 3*(i - 11) - bit's after
	
	add i, 2
	shl i, 2
	mov arr[i], bx
	shr i, 1
	sub i, 2
	pop ax

	jmp exit

exit:
	popa
endm

; 3.
addW macro arr, i
local addPrimary, addCarry, addAdditional, testZ, setZFlag, clearZFlag, testN, setNFlag, clearNFlag, exit
	push bx
	push cx

	; load new word
	mov bx, ax
	mov cl, dl
	loadW arr, i
	
addPrimary:
	add ax, bx
	jc addCarry
	jnc addAdditional
addCarry:
	add cl, 1
	jmp addAdditional

addAdditional:
	and cl, 0Fh
	and dl, 07h
	add dl, cl
	jmp testZ
	
testZ:
	cmp dl, 0
	jne clearZFlag
	cmp ax, 0
	jne clearZFlag
	je setZFlag
setZFlag:
	or dl, 2h
	jmp testN
clearZFlag:
	and dl, 0DFh
	jmp testN
	
testN:
	test dl, 04h
	je setNFlag
	jne clearNFlag
setNFlag:
	or dl, 40h
	jmp exit
clearNFlag:
	and dl, 0BFh
	jmp exit

exit:	
	pop cx
	pop bx
endm

subW macro arr, i
local addPrimary, addCarry, addAdditional, testZ, setZFlag, clearZFlag, testN, setNFlag, clearNFlag, exit
	push bx
	push cx

	; load new word
	mov bx, ax
	mov cl, dl
	loadW arr, i
	neg ax
	dec ax
	neg dx
	and dx, 0007h
	
addPrimary:
	add ax, bx
	jc addCarry
	jnc addAdditional
addCarry:
	add cl, 1
	jmp addAdditional

addAdditional:
	and cl, 0Fh
	and dl, 07h
	add dl, cl
	jmp testZ
	
testZ:
	cmp dl, 0
	jne clearZFlag
	cmp ax, 0
	jne clearZFlag
	je setZFlag
setZFlag:
	or dl, 2h
	jmp testN
clearZFlag:
	and dl, 0DFh
	jmp testN
	
testN:
	test dl, 04h
	je setNFlag
	jne clearNFlag
setNFlag:
	or dl, 40h
	jmp exit
clearNFlag:
	and dl, 0BFh
	jmp exit

exit:	
	pop cx
	pop bx
endm

stack segment para stack 'stack'
	db 100h dup(?)
stack ends

	arrSize equ 19
data segment para public 'data'
	array dw arrSize dup(0F0F0h)
	printBuffer db 19 dup(?), '$'
	counter db ?
	min dw ?
	max dw ?
data ends

code segment para public 'code'
assume cs:code, ds:data, ss:stack

Print19bitWord proc
	pusha
	
	mov si, 0
	mov cl, 5
	shl dl, cl
	
	mov cx, 3
dlPrint:	
	rcl dl, 1
	jc dlPrint1
	jnc dlPrint0
dlPrintEnd:
	inc si
	loop dlPrint
	mov cx, 16
	jmp axPrint
	
dlPrint1:
	mov printBuffer[si], '1'
	jmp dlPrintEnd
dlPrint0:
	mov printBuffer[si], '0'
	jmp dlPrintEnd
	
axPrint:
	rcl ax, 1
	jc alPrint1
	jnc alPrint0
alPrintEnd:
	inc si
	loop axPrint
	jmp printToScreen
	
alPrint1:
	mov printBuffer[si], '1'
	jmp alPrintEnd
alPrint0:
	mov printBuffer[si], '0'
	jmp alPrintEnd
	
printToScreen:
	lea dx, printBuffer
	mov ah, 09
	int 21h
	
	popa
	ret
Print19bitWord endp

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

addWTest proc
	mov si, 0h
	loadW array, si
	
	mov si, 2h
	addW array, si	
	
	ret
addWTest endp

writeWTest proc
	mov ax, 8765h
	mov dl, 05h
	
	mov si, 1
	writeW array, si
	
	ret
writeWTest endp

PrintNewLine proc
	mov dl, 0ah
	mov ah, 02h
	int 21h
	mov dl, 0dh
	mov ah, 02h
	int 21h
	ret
PrintNewLine endp

printArr proc

	mov si, 0
	mov cx, 16
loopMark:
	loadW array, si
	call Print19bitWord
	call PrintNewLine
	inc si
	loop cs:loopMark
	
	ret
printArr endp

doWork proc
	
	mov si, 0
	mov cx, 16
workLoop:
	loadW array, si
	test dl, 08h
	jz addMin
	jnz addMax
workLoopEnd:
	inc si
	loop workLoop
	ret
	
addMax:
	mov di, max
	addW array, di
	writeW array, si
	jmp workLoopEnd
addMin:
	mov di, min
	addW array, di
	writeW array, si
	jmp workLoopEnd
	
doWork endp

findMin proc
	mov si, 1
	mov min, 0
	mov counter, 15
	
findMinLoop:
	mov di, min
	loadW array, di
	subw array, si
	and dl, 20h
	cmp dl, 0
	jne newMin
	je findMinLoopEnd

findMinLoopEnd:
	inc si
	dec counter
	cmp counter, 0
	jne findMinLoop	
	ret
	
newMin:
	mov min, si
	jmp findMinLoopEnd 
findMin endp

findMax proc
	mov si, 1
	mov max, 0
	mov counter, 15
	
findMaxLoop:
	mov di, max
	loadW array, di
	subw array, si
	and dl, 20h
	cmp dl, 1
	jne newMax
	je findMaxLoopEnd
		
findMaxLoopEnd:
	inc si
	dec counter
	cmp counter, 0
	jne findMaxLoop
	ret
	
newMax:
	mov max, si
	jmp findMaxLoopEnd 
findMax endp
main:
	mov ax, data
	mov ds, ax
	
	; call loadWTest
	; call addWTest
	; call writeWTest
	
	call findMin
	call findMax
	
	call printArr
	call doWork
	call printArr
	
	mov ax, 4C00h
	int 21h
code ends
end main
