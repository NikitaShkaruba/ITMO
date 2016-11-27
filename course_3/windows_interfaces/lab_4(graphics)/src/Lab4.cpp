#include "stdafx.h" // wtf is this?
#include <windows.h>
#include <stdio.h> 

// Human readable signals for window action handlers
#define ID_EXIT		367
#define ID_COLOR	601

// Prototypes for functions below
LONG WINAPI handleWindowEvents(HWND, UINT, WPARAM,LPARAM);

// Just global variabe to be accessedfrom everywhere - It's not my code :)
COLORREF currentColor = RGB(10, 10, 10);
HBRUSH brush = CreateSolidBrush(currentColor);
int windowWidth, windowHeight;

// Figure
int figureDirection = 1, figureScale = 10, figureStep = 1;
const int figurePointsLength = 16; 
POINT figurePoints[figurePointsLength];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hWnd;
	MSG message;
	WNDCLASS windowClass;
    memset(&windowClass, 0, sizeof(WNDCLASS));

    windowClass.style = WS_TILED | CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = handleWindowEvents;
    windowClass.hInstance = hInstance;
	windowClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    windowClass.lpszClassName = L"Lab4";
	windowClass.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    
	RegisterClass(&windowClass);
	hWnd = CreateWindow(L"Lab4", L"Main Window", WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL);
	SetTimer(hWnd, 1, 20, (TIMERPROC) NULL);
	
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);
	
	while(GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    
	return message.wParam;
}

void initializeFigure() {	
	// Bottom right two spikes
	figurePoints[0].x =  + figureScale*(0);
	figurePoints[0].y = windowHeight/2 + figureScale*(1);

	figurePoints[1].x = figureScale*(1);
	figurePoints[1].y = windowHeight/2 + figureScale*(3);

	figurePoints[2].x = figureScale*(0.8);
    figurePoints[2].y = windowHeight/2 + figureScale*(0.8);

	figurePoints[3].x = figureScale*(3);
	figurePoints[3].y = windowHeight/2 + figureScale*(1);

	figurePoints[4].x = figureScale*(1);
	figurePoints[4].y = windowHeight/2 + figureScale*(0);	

	// Top right two spikes
	figurePoints[5].x = figureScale*(3);
	figurePoints[5].y = windowHeight/2 + figureScale*(-1);
	
	figurePoints[6].x = figureScale*(0.8);
	figurePoints[6].y = windowHeight/2 + figureScale*(-0.8);
	
	figurePoints[7].x = figureScale*(1);
	figurePoints[7].y = windowHeight/2 + figureScale*(-3);
	
	figurePoints[8].x = figureScale*(0);
	figurePoints[8].y = windowHeight/2 + figureScale*(-1);

	// Top left two spikes
	figurePoints[9].x = figureScale*(-1);
	figurePoints[9].y = windowHeight/2 + figureScale*(-3);

	figurePoints[10].x = figureScale*(-0.8);
    figurePoints[10].y = windowHeight/2 + figureScale*(-0.8);

	figurePoints[11].x = figureScale*(-3);
	figurePoints[11].y = windowHeight/2 + figureScale*(-1);

	figurePoints[12].x = figureScale*(-1);
	figurePoints[12].y = windowHeight/2 + figureScale*(0);	

	// Bottom left two spikes
	figurePoints[13].x = figureScale*(-3);
	figurePoints[13].y = windowHeight/2 + figureScale*(1);
	
	figurePoints[14].x = figureScale*(-0.8);
	figurePoints[14].y = windowHeight/2 + figureScale*(0.8);
	
	figurePoints[15].x = figureScale*(-1);
	figurePoints[15].y = windowHeight/2 + figureScale*(3);
}
void updateFigure() {
	// Bottom right two spikes
	for(int i = 0; i < figurePointsLength; i++) {
		figurePoints[i].x += figureStep * figureDirection;;
	}
}

void PaintPolygon(HDC hdc) {
	SelectObject(hdc, brush);
	Polygon(hdc, figurePoints, 16);
}
void RepaintWindow(HWND hWnd) {
	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
}

LONG WINAPI handleWindowEvents(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_PAINT:
		windowWidth = GetSystemMetrics(SM_CXSCREEN);
		windowHeight = GetSystemMetrics(SM_CYSCREEN);

		HDC hdc;
		PAINTSTRUCT ps;
		
		hdc = BeginPaint(hWnd, &ps);
		PaintPolygon(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER: 
		// Caclulate parameters/
		if (figurePoints[0].x > windowWidth) {
			figureDirection = -1;
		} else if (figurePoints[0].x < 0) {
			figureDirection = 1;
		}

		updateFigure();
		RepaintWindow(hWnd);
		SetTimer(hWnd, 1, 60, (TIMERPROC) NULL); // Reset timer
		break;
	case WM_KEYDOWN:
		if (wParam == VK_UP) {
			if (figureStep < 50) {
				figureStep += 1;
			} else {
				MessageBeep(0);
			}
		} else if (wParam == VK_DOWN) {
			if (figureStep > 0) {
				figureStep -= 1;
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
		windowWidth = GetSystemMetrics(SM_CXSCREEN);
		windowHeight = GetSystemMetrics(SM_CYSCREEN);
		initializeFigure();
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}