; It's Daniil's code. I wrote GUI.
; FASM CODE
;
;Условие:
;Вариант 11
;1 макрос: Чтение 15-битного слова
;2 макрос: Запись 15-битного слова
;3 Макрос: Подсчёт количества единиц в двоичной записи 15-битного слова
;Задание: Записать несколько чисел в память, прочитать их, и отобразить в виде таблицы [Число|кол-во единиц в нём]
;Баги и костыли:
;1. Программа не работает, если чисел больше 8. В девятом чисел корректно показываются только первые 7 бит, отсальные 8 нули. В десятом и последующих показываются только нули. Актуальое состояние памяти во время работы не проверял (лень было качать и настраивать отладчик), так что баг может быть как в записи / чтении, так и в отображении.
;2. Процедура, которая переводит число единиц в числе в строку (То бишь число ;8 в строку "8") не работает для двухзначиных чисел (то бишь если кол-во единиц ;в числе = [10,15]). Всё просто, мне лень было полностью писать логику ;процедуры ;IntegerToString, и я ограничился одним символом, что сильно упростило код.
;3. Тестилось на Windows 10 64-bit. 

format PE GUI 4.0
entry win_main
include 'H:\Fasm\INCLUDE\WIN32A.inc';Change this to your path to WIN32A.inc

section '.code' code readable executable
;some const defines
AMOUNT_OF_NUMBERS equ 8
WINDOW_WIDTH equ 220
WINDOW_HEIGHT equ 220
;ASCII codes for common symbols
ASCII_0 equ 48
ASCII_SPACE equ 32
ASCII_NEWLINE equ 10

;PRECONDITIONS
;cl = number1
;i = number2
;SYNOPSIS
;evaluates (number1 % number2)
;POSTCONDITIONS
;ch = (number1 % number2)
macro modulo i
{
    push ax
    push dx
;ax = n1
    xor ah, ah
    mov al, cl
;dl = n2
    mov dl, i
;ah = n1 % n2
    div dl
;ch = ah
    mov ch, ah

    pop dx
    pop ax
}

;PRECONDITIONS
;ebx = address of array
;i = index
;SYNOPSIS
;reads 15-bit word from memory into CPU
;POSTCONDITIONS
;ax = number
macro read15 i
{
local NeedAdditionalDecrease, TriBytes, TwoBytes, IndexIsMultiple7, EndRead
    push ebx
    push ecx
    push edx
;Adjust bx to point to i-th element of array
;using formula NewEBX = OldEBX + 2i + (i/8) - ((i % 8 == 0) ? : 0 : 1)
;P.S. Not 100% sure of this formula
    push eax
    add ebx, i
    add ebx, i
    mov eax, i
    xor edx, edx
    mov ecx, 8
    div ecx
    sub ebx, eax
    mov cl, i
    modulo 8
    cmp ch, 0
    jne NeedAdditionalDecrease
    inc ebx
NeedAdditionalDecrease:
    dec ebx
    pop eax
;if (i % 8) is 0 or 7, number is present in 2 bytes in memory. Otherwise, 3 bytes
    mov cl, i
    modulo 8
    cmp ch, 0
    je TwoBytes
    cmp ch, 7
    je TwoBytes
;Situation, where number is located in 3 bytes in memory
TriBytes:
;Read 1st byte into ah
    mov ah, [ebx]
    and ah, 01111111b
    shl ah, (7-i)
;Read part of 2nd byte into ah
    mov al, [ebx+1]
    shr al, (i+1)
;ah = upper 7 bits of word
    or ah, al
;Read part of 2nd byte into al
    mov al, [ebx+1]
    shl al, (7-i)
;Read 3rd byte into al
    mov dl, [ebx+2]
    shr dl, (i+1)
;al = lower 8 bits of word
    or al, dl
    jmp EndRead
;Situation, where number is located in 2 bytes in memory
TwoBytes:
    mov ah, [ebx]
    mov al, [ebx+1]
;if (i % 8) equals 0, we should shift bits to the right once. If it is equal 7, no shifts shall be done
    cmp ch, 7
    je IndexIsMultiple7
    shr ax, 1
IndexIsMultiple7:
    shl ax, 1
    shr ax, 1

EndRead:
;Make sure our number is 15-bit wide
    and ah, 01111111b

    pop edx
    pop ecx
    pop ebx
}
;PRECONDITIONS
;ebx = address of array
;i = index
;ax = number
;SYNOPSIS
;writes 15-bit word from CPU into memory
;POSTCONDITIONS
;none
macro write15 i
{
local NeedAdditionalDecrease, TriBytes, ModuloZero, ModuloSeven, EndWrite
    push eax
    push ebx
    push ecx
    push edx
;Make sure our number is 15-bit wide
    and ah, 01111111b
;Adjust bx to point to i-th element of array
;using formula NewEBX = OldEBX + 2i + (i/8) - ((i % 8 == 0) ? : 0 : 1)
;P.S. Not 100% sure of this formula
    push eax
    add ebx, i
    add ebx, i
    mov eax, i
    xor edx, edx
    mov ecx, 8
    div ecx
    sub ebx, eax
    mov cl, i
    modulo 8
    cmp ch, 0
    jne NeedAdditionalDecrease
    inc ebx
NeedAdditionalDecrease:
    dec ebx
    pop eax
;if (i % 8) is 0 or 7, number is present in 2 bytes in memory. Otherwise, 3 bytes
    mov cl, i
    modulo 8
    cmp ch, 0
    je ModuloZero
    cmp ch, 7
    je ModuloSeven
;Situation where number is located in 3 bytes in memory
TriBytes:
;Writing to 1st byte in memory, honouring previous value of untouched bits
    mov dl, [ebx]
    shr dl, i
    shl dl, i

    push eax

    shr ah, (7-i)
    or ah, dl
    mov [ebx], ah

    pop eax
;Writing to 2nd byte in memory
    push eax

    shl ah, (i+1)
    mov dl, ah
    shr al, (7-i)
    or dl, al
    mov [ebx+1], dl

    pop eax
;Writing to 3rd byte in memory, honouring previous value of untouched bits
    mov dl, [ebx+2]
    shl dl, (7-i)
    shr dl, (7-i)
    shl al, (i+1)

    or al, dl
    mov [ebx+2], al

    jmp EndWrite
;Situation, where (i % 8) == 0 and number can be stored in 2 bytes
ModuloZero:
    mov dl, [ebx+1]
    and dl, 00000001b
    shl ax, 1
    or al, dl;
    mov [ebx], ah
    mov [ebx+1], al

    jmp EndWrite
;Situation, where (i % 8) == 7 and number can be stored in 2 bytes
ModuloSeven:
    mov dl, [ebx]
    and dl, 10000000b
    or ah, dl
    mov [ebx], ah
    mov [ebx+1], al

    jmp EndWrite

EndWrite:
    pop edx
    pop ecx
    pop ebx
    pop eax
}
;PRECONDITIONS
;ax = number
;SYNOPSIS
;counts amount of '1's in a 15-bit word
;POSTCONDITIONS
;ax = '1's count
macro count15
{
local ShiftBits, Add1
    push ecx
    push edx

;Make sure our number is 15-bit wide
    and ah, 01111111b
;Counting is done with simple in-loop shifting with checking shifted-out bit's value
    xor dx, dx
    mov cx, 15
ShiftBits:
	shr ax, 1
	jc Add1
	dec dx
    Add1:
	inc dx
    loop ShiftBits

    mov ax, dx

    pop edx
    pop ecx
}
;PRECONDITIONS
;ebx = address of Array to fill
;[index] = list of indexes
;SYNOPSIS
;fills array with a pattern: a[i] = i*i
;POSTCONDITIONS
;none
macro FillArrayWithSquares [index]
{
    mov ax, index*index
    write15 index
}
;PRECONDITIONS
;eax = 15-bit number
;ebx = address of string to store result
;SYNOPSIS
;Writes string of bit-version of a 15-bit number (e.g. '011010010100110')
;POSTCONDITIONS
;none
Number15ToStr:
    push eax
    push ecx
    push edx

    mov ecx, 15
    rcl ax, 1
.TranslateLoop:
    mov dl, ASCII_0
    rcl ax, 1
    jc .Add1
    dec dl
.Add1:
    inc dl
    mov [ebx], dl
    inc ebx
    loop .TranslateLoop
    sub ebx, 15



    pop edx
    pop ecx
    pop eax
ret
;PRECONDITIONS
;eax = 15-bit number
;ebx = address of string to store result
;SYNOPSIS
;Counts amount of '1's in number, and stores that as string
;e.g. for 011010010100110 it would store '7'
;POSTCONDITIONS
;none
Count15ToStr:
    push dx

    count15
    mov dl, ASCII_0
    add dl, al
    mov [ebx], dl

    pop dx
ret
;PRECONDITIONS
;none
;SYNOPSIS
;Fills array with 15bit-wide numbers
;POSTCONDITIONS
;none
FillArrayWith15BitNumbers:
     push eax
     push ebx

     mov ebx, init
     FillArrayWithSquares 0,1,2,3,4,5,6,7;, ...up to (AMOUNT_OF_NUMBERS - 1)
     pop ebx
     pop eax
ret
;Help-Macro-1 for Read15Ecx
Macro CmpJe [index]
{
    cmp ecx, (AMOUNT_OF_NUMBERS - index)
    je read#index
}
;Help-Macro-2 for Read15Ecx
Macro ReadLabels [index]
{
    read#index: read15 index
    ret
}
;PRECONDITIONS
;ECX = index
;SYNOPSIS
;Performs a read15 operation, but uses ECX value as index
;POSTCONDITIONS
;none
Read15Ecx:
    CmpJe 0,1,2,3,4,5,6,7;, ...up to (AMOUNT_OF_NUMBERS - 1)
    ReadLabels 0,1,2,3,4,5,6,7;, ...up to (AMOUNT_OF_NUMBERS - 1)
ret
;PRECONDITIONS
;ecx = amount of numbers
;ecx is inter-dependent with Read15ecx procedure, if one changes, change another too
;SYNOPSIS
;reads 15bit-wide number from 'init' array, then
;stores it's String representation in 'szNumber' string, then
;stores it's '1's count int 'szOnes' string, end
;POSTCONDITIONS
;none
ReadNextNumber:
    push ebx

    mov ebx, init
    call Read15Ecx

    mov ebx, szNumber
    call Number15ToStr

    mov ebx, szOnes
    call Count15ToStr

    pop ebx
ret
  win_main:
	call FillArrayWith15BitNumbers;BL

	invoke GetModuleHandle,0
	mov [wcex.hInstance],eax
	mov eax,sizeof.WNDCLASSEX
	mov [wcex.cbSize],eax
	mov [wcex.lpfnWndProc],WndProc
	mov [wcex.style],CS_HREDRAW+CS_VREDRAW

	invoke LoadIcon,[wcex.hInstance],IDI_APPLICATION
	mov [wcex.hIcon],eax
	mov [wcex.hIconSm],eax
	invoke LoadCursor,NULL,IDC_ARROW
	mov [wcex.hCursor],eax
	mov [wcex.hbrBackground],COLOR_WINDOW+1
	mov dword [wcex.lpszClassName],szClass
	mov [wcex.cbClsExtra],0
	mov [wcex.cbWndExtra],0
	mov dword [wcex.lpszMenuName],NULL

	invoke RegisterClassEx,wcex
	test eax,eax
	jz reg_error

	invoke CreateWindowEx,0,szClass,szTitle,WS_OVERLAPPEDWINDOW,\
			      CW_USEDEFAULT,CW_USEDEFAULT,\
			      WINDOW_WIDTH,WINDOW_HEIGHT,\
			      NULL,NULL,[wcex.hInstance],NULL
	test eax,eax
	jz cr_error
	mov [h_wnd],eax

	invoke ShowWindow,[h_wnd],SW_SHOWNORMAL
	invoke UpdateWindow,[h_wnd]

  msg_loop:
	invoke GetMessage,msg,NULL,0,0
	cmp eax,1
	jb exit
	jne msg_loop
	invoke TranslateMessage,msg
	invoke DispatchMessage,msg
	jmp msg_loop

  reg_error:
	invoke MessageBox,NULL,szRegError,szTitle,MB_ICONERROR+MB_OK
	jmp exit

  cr_error:
	invoke MessageBox,NULL,szCreateError,szTitle,MB_ICONERROR+MB_OK

  exit:
	invoke	ExitProcess,[msg.wParam]

proc WndProc uses ebx esi edi,hwnd,wmsg,wparam,lparam
	cmp [wmsg],WM_PAINT
	je .PAINT
	cmp [wmsg],WM_DESTROY
	je .DESTROY
  .DEFAULT:
	invoke DefWindowProc,[hwnd],[wmsg],[wparam],[lparam]
	jmp .DONE

  .PAINT:
	invoke BeginPaint,[hwnd],ps
	mov [hdc],eax
	invoke TextOut, [hdc], 5, ebx, description, 35
	mov ebx, 40
	mov ecx, AMOUNT_OF_NUMBERS
  .printArrayLoop:
	call ReadNextNumber ;BL

	invoke TextOut, [hdc], 5, ebx, szNumber, 15
	invoke TextOut, [hdc], 150, ebx, szOnes, 1
	add ebx, 15
	loop .printArrayLoop

	invoke EndPaint,[hwnd],ps
	jmp .DONE

  .DESTROY:
	invoke PostQuitMessage,0
	xor eax,eax

  .DONE:
	ret

endp

section '.idata' import data readable writeable
  library kernel,'KERNEL32.DLL',\
	  user,'USER32.DLL',\
	  gdi,'GDI32.DLL'

  import kernel,\
	 GetModuleHandle,'GetModuleHandleA',\
	 ExitProcess,'ExitProcess'

  import user,\
	 RegisterClassEx, 'RegisterClassExA',\
	 CreateWindowEx, 'CreateWindowExA',\
	 ShowWindow, 'ShowWindow',\
	 UpdateWindow, 'UpdateWindow',\
	 GetMessage, 'GetMessageA',\
	 TranslateMessage, 'TranslateMessage',\
	 DispatchMessage, 'DispatchMessageA',\
	 MessageBox, 'MessageBoxA',\
	 DefWindowProc, 'DefWindowProcA',\
	 BeginPaint, 'BeginPaint',\
	 EndPaint, 'EndPaint',\
	 PostQuitMessage, 'PostQuitMessage',\
	 LoadIcon, 'LoadIconA',\
	 LoadCursor, 'LoadCursorA'

  import gdi,\
	 TextOut,'TextOutA'

section '.data' readable writeable
;init = array to store 15bit-wide numbers
;szNumber = String to store binary reoresentation of one 15bit number
;szOnes = String to store decimal amount of '1's of one 15bit number
;description = Text to display at the Top
;Anything else = Not that relevant / Just template;
  init db 100 dup 0
  szNumber TCHAR "???????????????",0
  szOnes TCHAR "?",0
  description TCHAR "15 bit word:                  1's?", 0

  szClass TCHAR "lAB 8", 0
  szTitle TCHAR "lAB 8", 0
  szRegError TCHAR "Call to RegisterClassEx failed!", 0
  szCreateError TCHAR "Call to CreateWindowEx failed!", 0
  wcex WNDCLASSEX
  ps PAINTSTRUCT
  msg MSG
  h_wnd dd 0
  hdc dd 0