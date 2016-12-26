#include <windows.h>
#include <time.h>
#include <tchar.h>
#include "conio.h"

enum directions { FORWARD, BACK };
directions currentDirection = FORWARD;
HBITMAP hbmp = (HBITMAP)LoadImage(NULL, "C:/Users/username/other/path/to/bmp/img.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); // Todo: Hardcode your own path
SIZE bmpSize = { 139, 139 }; // Todo: Hardcode your own bmp size
int step = 0;
POINT dcOffset = { 0, 0 };
POINT bmpOffset = { 0, 0 };
int screenWidth = 0, screenHeight = 0;

HWND hWnd;
HDC hdc;
HHOOK keyPressHook;
BLENDFUNCTION blendFunc;

void CALLBACK Do_Step(_In_ HWND hWnd, _In_ UINT uMsg, _In_ UINT_PTR idEvent, _In_ DWORD dwTime) {
	bmpOffset.x = (currentDirection == FORWARD) ? bmpOffset.x + step : bmpOffset.x - step;
	UpdateLayeredWindow(hWnd, NULL, &bmpOffset, &bmpSize, hdc, &dcOffset, 0, &blendFunc, ULW_ALPHA);

	if (bmpOffset.x + bmpSize.cx > screenWidth) {
		currentDirection = BACK;
    } else if (bmpOffset.x < 0) {
		currentDirection = FORWARD;
	}
}

void UpdateDesktopSize(int& horizontal, int& vertical) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow(); // Get a handle to the desktop window
	GetWindowRect(hDesktop, &desktop); // Get the size of screen to the variable desktop
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

LRESULT __declspec(dllexport)__stdcall  CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
		if (p->vkCode == 0x27) { // Right arrow
			step++;
		}
		if (p->vkCode == 0x25 && step > 0) { // Left arrow
			step--;
		}
	}

	return CallNextHookEx(keyPressHook, nCode, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UpdateDesktopSize(screenWidth, screenHeight);
	TCHAR WinName[] = _T("MainFrame");
	WNDCLASSEX WndEx = { 0 };
	WndEx.cbSize = sizeof(WNDCLASSEX);
	WndEx.lpfnWndProc = DefWindowProc;
	WndEx.hInstance = hInstance;
	WndEx.lpszClassName = WinName;
	RegisterClassEx(&WndEx);
	hWnd = CreateWindowEx(WS_EX_LAYERED, WinName, 0, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	SetTimer(hWnd, 1, 10, (TIMERPROC)Do_Step);

	HDC hdcScreen = GetDC(0);
	hdc = CreateCompatibleDC(hdcScreen);
	ReleaseDC(0, hdcScreen);
	(HBITMAP)SelectObject(hdc, hbmp);

	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.SourceConstantAlpha = 255;
	blendFunc.AlphaFormat = AC_SRC_ALPHA;
	UpdateLayeredWindow(hWnd, 0, &bmpOffset, &bmpSize, hdc, &dcOffset, 0, &blendFunc, ULW_ALPHA);

	ShowWindow(hWnd, SW_SHOW);
	keyPressHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, 0, 0);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
