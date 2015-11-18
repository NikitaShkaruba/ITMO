format PE GUI 4.0
entry win_main
include 'C:\Users\Iaaae\Desktop\Fasm\INCLUDE\WIN32A.inc'

section '.code' code readable executable

  win_main:
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

        ; create the window
        invoke CreateWindowEx,0,szClass,szTitle,WS_OVERLAPPEDWINDOW,\
                              CW_USEDEFAULT,CW_USEDEFAULT,\
                              280,220,NULL,NULL,[wcex.hInstance],NULL
        test eax,eax
        jz cr_error
        mov [h_wnd],eax

        ; show and update the window
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
        invoke  ExitProcess,[msg.wParam]

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
        invoke TextOut, [hdc], 5, ebx, description, 45
        mov ebx, 20
        mov ecx, 10
  .printArrayLoop:
        ; EAX to string
        invoke TextOut, [hdc], 5, ebx, szGreeting, 16
        ; Call is 1?
        invoke TextOut, [hdc], 150, ebx, szGreeting, 1
        add ebx, 15
        loop .printArrayLoop

        invoke EndPaint,[hwnd],ps
        jmp .DONE

  .DESTROY:
        ; PostQuitMessage(0)
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
  szGreeting TCHAR "1101010111010101101!",0
  szIsOne TCHAR "1",0
  description TCHAR "19 bit word:                  how much ones?", 0

  szClass TCHAR "lAB 8", 0
  szTitle TCHAR "lAB 8", 0
  szRegError TCHAR "Call to RegisterClassEx failed!", 0
  szCreateError TCHAR "Call to CreateWindowEx failed!", 0
  wcex WNDCLASSEX
  ps PAINTSTRUCT
  msg MSG
  h_wnd dd 0
  hdc dd 0