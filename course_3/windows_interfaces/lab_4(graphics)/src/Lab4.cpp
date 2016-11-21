#include "stdafx.h" // wtf is this?
#include <windows.h>
#include <stdio.h> 

// Human readable signals for window action handlers
#define ID_EXIT		367
#define ID_COLOR	601

// Prototypes for functions below
LONG WINAPI handleWindowEvents(HWND, UINT, WPARAM,LPARAM);

// Just global variabe to be accessedfrom everywhere - It's not my code :)
HINSTANCE hInst;
HANDLE hThr;
WINDOWINFO hInfo;
COLORREF currentColor = RGB(204, 0, 0);
HPEN pen = CreatePen(PS_SOLID, 1, currentColor), oldPen;
HBRUSH brush = CreateSolidBrush(currentColor), oldBrush;
POINT points[4];
int offset = 0, w, h, direction = 1;
int timerDelay = 100;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hWnd;
	MSG message;
	WNDCLASS windowClass;
    memset(&windowClass, 0, sizeof(WNDCLASS));

    windowClass.style = WS_TILED | CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = handleWindowEvents;
    windowClass.hInstance = hInst = hInstance;
	windowClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    windowClass.lpszClassName = L"Lab4";
	windowClass.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    
	RegisterClass(&windowClass);
	hWnd = CreateWindow(L"Lab4", L"Main Window", WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL);
	SetTimer(hWnd, 1, timerDelay, (TIMERPROC) NULL);
	
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);
	
	while(GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    
	return message.wParam;
}

void PaintPolygon(HDC hdc) {
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	points[0].x = w/2+15+offset;
	points[1].x = w/2+35+offset;
	points[2].x = w/2-15+offset;
	points[3].x = w/2-35+offset;
	points[0].y = h/2+10;
	points[1].y = h/2-10;
	points[2].y = h/2-10;
	points[3].y = h/2+10;

	Polygon(hdc, points, 4);
}

void RepaintWindow(HWND hWnd) {
	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
}

LONG WINAPI handleWindowEvents(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_PAINT:
		w = GetSystemMetrics(SM_CXSCREEN);
		h = GetSystemMetrics(SM_CYSCREEN);

		HDC hdc;
		PAINTSTRUCT ps;
		
		hdc = BeginPaint(hWnd, &ps);
		PaintPolygon(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER: 
		if (direction == -1) {
			if (points[3].x - 10 >= 0) {
				offset -= 10;
				RepaintWindow(hWnd);
			} else {
				direction = 1;
			}
		}
		if (direction == 1){
			if (points[1].x + 10 <= w){
				offset += 10;
				RepaintWindow(hWnd);
			} else {
				direction = -1;
			}
		}
		SetTimer(hWnd, 1, timerDelay, (TIMERPROC) NULL); // Reset timer
		break;
	case WM_KEYDOWN:
		if (wParam == VK_UP) {
			if (timerDelay > 50) {
				timerDelay -= 10; 
			} else {
				MessageBeep(0);
			}
		} else if (wParam == VK_DOWN) {
			if (timerDelay < 10000) {
				timerDelay += 10; 
			} else {
				MessageBeep(0);
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == ID_EXIT)
			exit(0);
		break;
	case WM_CREATE:
		w = GetSystemMetrics(SM_CXSCREEN);
		h = GetSystemMetrics(SM_CYSCREEN);

		points[0].x = w/2+15+offset;
		points[1].x = w/2+35+offset;
		points[2].x = w/2-15+offset;
		points[3].x = w/2-35+offset;
		points[0].y = h/2+10;
		points[1].y = h/2-10;
		points[2].y = h/2-10;
		points[3].y = h/2+10;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}