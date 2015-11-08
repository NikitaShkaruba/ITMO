; Hypotetic processor's word - 19 bit
; Macroses:
;	1. read element  by index from word array
;	2. write element by index to   word array
; 	3. word's addition
; Work:
; 	- To every negative add max positive element
; 	- To every positive add min negative element
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
	shl i,	1
	mov ax, arr[i]
	shr i,  1 
	mov cx, i
	mul cx, 3
	add cx, 3
	shl ax, cl
	
	; shr bx, 16 - 3 - 3*(i)
	inc i
	shl i,	1
	mov bx, arr[i]
	shr i, 	1
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
	shl i, 	1
	mov ax, arr[i]
	shr i, 	1
	dec i
	mov cx, i
	sub cx, 5
	mul cx, 3
	add cx, 2
	shl ax, cl
	
	; shr bx, 16 - 2 - 3*(i - 5)
	add i, 	2
	shl i, 	1
	mov bx, arr[i]
	shr i, 	1
	sub i, 	2
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
	add i, 	2
	shl i, 	1
	mov ax, arr[i]
	shr i, 	1
	sub i, 	2
	mov cx, i
	sub cx, 10
	mul cx, 3
	inc cx
	shl ax, cl
	
	; shr bx, 16 - 1 - 3*(i - 10) 
	add i, 	3
	shl i, 	1
	mov bx, arr[i]
	shr i, 	1
	sub i, 	3
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
	cmp i, 	5
	jl Acase0_4
	je Acase5
	cmp i, 	10
	jl Acase6_9
	je Acase10
	jmp Acase11_15
		
Acase0_4:
	shl i, 	1
	mov dx, arr[i]
	
	;rol dx, 3 + (i)
	shr i, 	1
	mov cx, i
	inc cx
	mul cx, 3
	rol dx, cl
	jmp PostLoadAddition

Acase5:
	shl i, 	1
	mov dx, arr[i]
	
	and dx, 01h 		;clear other bytes
	add i, 	2
	mov bx, arr[i]
	and bx, 0C000h
	or  dx,	bx
	rol dx, 2
	sub i, 	2
	shr i, 	1
	jmp PostLoadAddition
	
Acase6_9:
	inc i
	shl i, 	1
	mov dx, arr[i]
	
	; rol dx, 5 + 3*(i - 6) ; 
	shr i, 	1
	dec i
	mov cx, i
	sub cx, 6
	mul cx, 3
	add cx, 5
	rol dx, cl
	jmp PostLoadAddition

Acase10:
	inc i
	shl i, 	1
	mov dx, arr[i]
	
	and dx, 0003h 		;clear other bytes
	add i, 	2
	mov bx, arr[i]
	and bx, 8000h
	or  dx, bx
	rol dx, 1
	sub i, 	2
	shr i, 	1
	dec i
	jmp PostLoadAddition
	
Acase11_15:
	add i, 	2
	shl i, 	1
	mov dx, arr[i]
	
	; rol dx, 4 + 3*(i - 11)
	shr i, 	1
	sub i, 	2
	mov cx, i
	sub cx, 11
	mul cx, 3
	add cx, 4
	rol dx, cl
	jmp PostLoadAddition

PostLoadAddition:
	; set all the flags
	and dx, 0007h 			;coz my addition is the last 3 bits
	
	pop cx
	pop bx
endm

; 2.
writeW macro arr, i
local case0_4, case5, case6_9, case10, case11_15, exit
	;add ax, 0AB75h
	pusha
	
case0_4:
	; 3*(i) - bit's before
	; 3 + 3*(i) - bit's after
	
	; clear past bytes, save others
	shl i, 	1
	mov bx, arr[i]
	shr i, 	1
	
	mov cx, i 			;shr bx, 16 - 3*i
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
	shl bx, cl			;shl bx, 16 - 3 - 3*i 
	mov cx, i
	mul cx, 3
	add cx, 3
	shr ax, cl 			;shr ax, 3 + 3*i
	add bx, ax
	;mov bx, 0FF00h; !!!!!!!!!!!!!!1      - если это уже не нужно, может стоит удалить?
	
	shl i, 	1
	mov arr[i], bx
	shr i, 	1
	pop ax
	; load primary second part
	push ax
	inc i
	shl i, 	1
	mov bx, arr[i]
	shr i, 	1
	dec i
	
	shl bx, cl			;shl bx, 3 + 3*i
	neg cx		
	add cx, 16
	shl ax, cl			;shl ax, 16 - 3 - 3*(i)
	shr ax, cl			;shr ax, 16 - 3 - 3*(i)
	add bx, ax
	mov cx, i
	mul cx, 3
	add cx, 3
	ror bx, cl			;ror bx, 3 + 3*i
	
	shl i, 	1
	add i, 	2
	mov arr[i], bx
	sub i, 	2
	shr i, 	1
	pop ax

	jmp exit
case5:
	shl i, 	1			; i == 5
	mov bx, arr[i]
	shr i, 	1
	
	push dx
	and bx, 0FFFEh 			;0001h
	shr dl, 2
	add bx, dx
	shl i, 	1
	mov arr[i], bx
	shr i, 	1
	pop dx
	
	mov i, 	6 			;inc i. what?	; i == 6
	shl i, 	1
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
	shr i, 	1
	dec i
	pop ax
	
	; load primary last 2 bits
	add i, 2			; i == 7
	shl i, 1
	mov bx, arr[i]
	
	push ax
	shl bx, 2
	and ax, 0003h
	add bx, ax
	
	ror bx, 2
	mov arr[i], bx
	shr i, 	1
	sub i, 	2
	pop ax
	
	jmp exit
case6_9:
	; 2 + 3*(i - 6) - bit's before
	; 5 + 3*(i - 6) - bit's after
	
	; clear past bytes, save others
	inc i
	shl i, 	1
	mov bx, arr[i]
	shr i, 	1
	dec i
	
	mov cx, 		 	;shr bx, 16 - 2 - 3*(i - 6)
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
	shl bx, cl			;shl bx, 16 - 2 - 3*(i - 6)
	mov cx, i
	sub cx, 6
	mul cx, 3
	add cx, 5
	shr ax, cl 			; shr ax, 5 + 3*(i - 6)
	add bx, ax
	inc i
	
	shl i, 	1
	mov arr[i], bx
	shr i, 	1
	dec i
	pop ax
	; load primary second part
	push ax
	add i, 	2
	shl i, 	1
	mov bx, arr[i]
	shr i, 	1
	sub i, 	2
	
	shl bx, cl			;shl bx, bit's after. cl is proper from last cl's calls
	neg cx
	add cx, 16
	shl ax, cl			;shl ax, 16 - 3 - 3*(i)
	shr ax, cl			;shr ax, 16 - 3 - 3*(i)
	add bx, ax
	mov cx, i
	sub cx, 6
	mul cx, 3
	add cx, 5
	ror bx, cl			;ror bx, 5 + 3*(i - 6) - bit's after
	
	add i, 	2
	shl i, 	2
	mov arr[i], bx
	shr i, 	1
	sub i, 	2
	pop ax

	jmp exit
case10:
	inc i
	shl i, 	1	
	mov bx, arr[i] 			;i == 10
		
	push dx
	and bx, 0FFFCh 			;clear last bytes
	shr dl, 1
	add bx, dx
	
	mov arr[i], bx
	shr i, 	1
	dec i
	pop dx
	
	add i, 	2			;i == 6
	shl i, 	1
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
	shr i, 	1
	sub i, 	2
	pop ax
	
	; load primary last bit
	add i, 	3			;i == 7
	shl i, 	1
	mov bx, arr[i]
	
	push ax
	shl bx, 1
	and ax, 0001h
	add bx, ax
	ror bx, 1
	
	mov arr[i], bx
	shr i, 	1
	sub i, 	3
	pop ax
	
	jmp exit
case11_15:
	; 1 + 3*(i - 11) - bit's before
	; 4 + 3*(i - 11) - bit's after
	
	; clear past bytes, save others
	inc i
	shl i, 	1
	mov bx, arr[i]
	shr i, 	1
	dec i
	
	mov cx, i 
	sub cx, 11
	mul cx, 3
	neg cx
	add cx, 15
	shr bx, cl			;shr bx, 16 - 1 - 3*(i - 11)
	; load addition
	push dx
	shl bx, 3
	and dl, 07h
	add bl, dl
	pop dx
	; load primary first part
	push ax
	sub cx, 3
	shl bx, cl			;shl bx, 16 - 2 - 3 - 3*(i - 6)
	mov cx, i
	sub cx, 11
	mul cx, 3
	add cx, 4
	shr ax, cl 			;shr ax, 4 + 3*(i - 11)
	add bx, ax
	inc i
	
	shl i, 	1
	mov arr[i], bx
	shr i, 	1
	dec i
	pop ax
	; load primary second part
	push ax
	add i, 	2
	shl i, 	1
	mov bx, arr[i]
	shr i, 1
	sub i, 2
	
	shl bx, cl			;shl bx, bit's after. cl is proper from last cl's calls
	neg cx
	add cx, 16
	shl ax, cl			;shl ax, 16 - 4 - 3*(i - 11)
	shr ax, cl			;shr ax, 16 - 4 - 3*(i - 11)
	add bx, ax
	mov cx, i
	sub cx, 11
	mul cx, 3
	add cx, 4
	ror bx, cl			;ror bx, 4 + 3*(i - 11) - bit's after
	
	add i, 	2
	shl i, 	2
	mov arr[i], bx
	shr i, 	1
	sub i, 	2
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
	or dl, 	2h
	jmp testN
clearZFlag:
	and dl, 0DFh
	jmp testN
	
testN:
	test dl,04h
	je setNFlag
	jne clearNFlag
setNFlag:
	or dl, 	40h
	jmp exit
clearNFlag:
	and dl, 0BFh
	jmp exit

exit:	
	pop cx
	pop bx
endm

cmpW macro arr, i ; is subs
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
	or dl, 	2h
	jmp testN
clearZFlag:
	and dl,	0DFh
	jmp testN
	
testN:
	test dl,04h
	jne setNFlag	; OMG, I WERE TRYING TO WRITE SUBW IN THIS TONN OF NOT READABLE CODE. IT'S MY DAMNED CRUTCH. I AM SO SORRY ABOUT THIS
	je clearNFlag
setNFlag:
	or dl,	40h
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
	array dw arrSize dup(0FEFFh)
	printBuffer db 19 dup(?), '$'
	counter db ?
	min dw 0002h
	max dw 000Ch
data ends

code segment para public 'code'
assume cs:code, ds:data, ss:stack

PrintW proc
	pusha
	
	; prepare dl for rcl needed bit's
	shl dl, 5
	
	mov si, 0
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
	mov ah, 09h
	int 21h
	
	popa
	ret
PrintW endp

; void loadW(int idx)
loadWShell proc
	mov bp,	sp
	mov si, [bp + 2]
	
	loadW array, si
	
	ret 2
loadWShell endp

loadWTest proc
	pusha 
	
	mov si,	0			;case0-4 addition, _4 primary
	loadW array, si	
	
	mov si, 5			;case5
	loadW array, si	
	
	mov si, 7			;case6-9
	loadW array, si	
	
	mov si, 10			;case10
	loadW array, si	
	
	mov si, 12			;case11-15
	loadW array, si
	
	popa
	ret
loadWTest endp

; void addW(int idx)
addWShell proc
	mov bp, sp
	mov si, bp[2]
	
	addW array, si
	
	ret 2
addWShell endp

; void cmpW(int idx)
cmpWShell proc
	mov bp, sp
	mov si, bp[2]
	
	cmpW array, si
	
	ret 2
cmpWShell endp

addWTest proc
	pusha
	
	mov si, 0h
	loadW array, si
	
	mov si, 2h
	addW array, si	
	
	popa
	ret
addWTest endp

; void writeW(int idx)
writeWShell proc
	mov bp, sp
	mov si, [bp + 2]
	
	writeW array, si
	
	ret 2
writeWShell endp

writeWTest proc
	pusha
	
	mov ax, 0ABCDh
	mov dl, 03h
	
	mov cx, 16
lp:
	mov si, cx
	push cx
	call writeWShell
	loop lp
	
	popa
	ret
writeWTest endp

PrintNewLine proc
	pusha
	mov dl, 0ah
	mov ah, 02h
	int 21h
	mov dl, 0dh
	mov ah, 02h
	int 21h
	
	popa
	ret
PrintNewLine endp

printArr proc
	pusha

	mov si, 0
	mov cx, 16
loopMark:
	push si
	call loadWShell
	call PrintW
	call PrintNewLine
	inc si
	loop loopMark
	
	call PrintNewLine
	
	popa
	ret
printArr endp

doWork proc
	pusha
	mov si, 0
	mov cx, 16
workLoop:
	push si
	call loadWShell
	test dl, 04h
	jz addMin
	jnz addMax
workLoopEnd:
	inc si
	loop workLoop
	
	;call writeWTest
	popa
	ret
	
addMax:
	push max
	call addWShell
	push si
	call writeWShell
	jmp workLoopEnd
addMin:
	push min
	call addWShell
	push si
	call writeWShell
	jmp workLoopEnd
	
doWork endp

findMin proc
	pusha
	mov si, 1
	mov min,0
	mov counter, 15 		;I haven't enough registers
	
findMinLoop:
	push min 
	call loadWShell
	push si
	call cmpWShell
	and dl, 40h
	cmp dl, 0
	je findMinLoopEnd
	jne newMin

findMinLoopEnd:
	inc si
	dec counter
	cmp counter, 0
	jne findMinLoop
	
	popa
	ret
	
newMin:
	mov min, si
	jmp findMinLoopEnd 
findMin endp

findMax proc
	pusha
	mov si,	 1
	mov max, 0
	mov counter, 15
	
findMaxLoop:
	push max
	call loadWShell
	push si
	call cmpWShell
	and dl, 40h
	cmp dl, 0
	je newMax
	jne findMaxLoopEnd
		
findMaxLoopEnd:
	inc si
	dec counter
	cmp counter, 0
	jne findMaxLoop
	
	popa
	ret
	
newMax:
	mov max, si
	jmp findMaxLoopEnd 
findMax endp

main:
	mov ax, data
	mov ds, ax
	
	;call loadWTest
	;call addWTest
	;call writeWTest
	
	call findMin
	call findMax
	
	call printArr
	call doWork
	call printArr

	mov ax, 4C00h
	int 21h
code ends
end main
