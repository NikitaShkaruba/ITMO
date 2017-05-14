#include <windows.h>
#include <math.h>
#include <cmath>
#include <tchar.h>
#include <strsafe.h>
#include <errno.h>
#include "Button.h"

#define TITLE_TEXTBOX_ID		577
#define WIDTH_TEXTBOX_ID		587
#define HEIGHT_TEXTBOX_ID		597
#define ADD_NEW_BUTTON_ID		549
#define INFO_TEXTBOX_ID	519
#define MAX_CHARS	16

HWND mainHandle;
HINSTANCE hInstance;

TCHAR buf[MAX_CHARS], title[MAX_CHARS];
int width, height, tmp;
int maxWidth = 170, maxHeight = 170;

LONG WINAPI WndProc(HWND, UINT, WPARAM,LPARAM);
void handleTextboxes(WPARAM param);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    WNDCLASS w;
    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
	hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    w.lpszClassName = L"Lab3";
	w.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&w);
    mainHandle = CreateWindow(L"Lab3", L"Lab3", WS_CAPTION | WS_POPUPWINDOW, 200, 200, 200, 800, NULL, NULL, hInstance, NULL);

	// create 3 textboxes (btn title, width, height)
	HWND hTitle = CreateWindow(L"Edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT, 120, 8, 60, 20, mainHandle, (HMENU)TITLE_TEXTBOX_ID, hInstance, 0);
	HWND hWidth = CreateWindow(L"Edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER, 120, 38, 60, 20, mainHandle, (HMENU)WIDTH_TEXTBOX_ID, hInstance, 0);
	HWND hHeight = CreateWindow(L"Edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER, 120, 68, 60, 20, mainHandle, (HMENU)HEIGHT_TEXTBOX_ID, hInstance, 0);
	HWND hInfo = CreateWindow(L"Edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY, 10, 128, 170, 20, mainHandle, (HMENU)INFO_TEXTBOX_ID, hInstance, 0);
	
	SetWindowText(hTitle, L"Btn");		// def title
	SetWindowText(hWidth, L"50");		// def width
	SetWindowText(hHeight, L"20");		// def height

	// create button to create new btns
	HWND hAddBtn = CreateWindow(L"Button", NULL, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 98, 170, 20, mainHandle, (HMENU)ADD_NEW_BUTTON_ID, hInstance, 0);
	SetWindowText(hAddBtn, L"Add Button");

    ShowWindow(mainHandle, nCmdShow);
    UpdateWindow(mainHandle);
	while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
	return msg.wParam;
}
LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {
	HDC hdc;
	PAINTSTRUCT ps;
	
    switch (Message){
    case WM_DESTROY: 
        PostQuitMessage(0);
        break;
	case WM_COMMAND:
		if (HIWORD(wparam) == EN_UPDATE) {
			handleTextboxes(wparam);
		}
		
		if (HIWORD(wparam) == BN_CLICKED)
			if (LOWORD(wparam) == ADD_NEW_BUTTON_ID) {
				// Add-new-button is clicked
				if (width == 0 || height == 0 || wcslen(title) == 0) {
					Button *btn = new Button(hInstance, mainHandle);
				} else {
					Button *btn = new Button(hInstance, mainHandle, title, width, height);
				}
			} else {
				// Added button is clicked
				GetDlgItemText(mainHandle, LOWORD(wparam), buf, MAX_CHARS);
				StringCbPrintf(buf, sizeof(buf), L"%s clicked", buf);
				SetDlgItemText(mainHandle, INFO_TEXTBOX_ID, buf);
			}
		
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		TextOut(hdc, 10, 10, L"button title:", 13);
		TextOut(hdc, 10, 40, L"button width:", 13);
		TextOut(hdc, 10, 70, L"button height:", 14);

		EndPaint(hwnd, &ps);
		break;
    default:
        return DefWindowProc(hwnd, Message, wparam, lparam);
    }

    return 0;
}

void SetClickedButtonTitleToTextbox(int CID, int data) {
	StringCbPrintf(buf, sizeof(buf), L"%d", data);
	SetDlgItemText(mainHandle, CID, buf);
}
void handleTextboxes(WPARAM param) {
	// handle title-textbox
	if (LOWORD(param) == TITLE_TEXTBOX_ID) {
		GetDlgItemText(mainHandle, TITLE_TEXTBOX_ID, title, MAX_CHARS);
	}
	
	// handle width-textbox 
	if (LOWORD(param) == WIDTH_TEXTBOX_ID) {
		// get text, convert to int
		GetDlgItemText(mainHandle, WIDTH_TEXTBOX_ID, buf, MAX_CHARS);
		tmp = _tstoi(buf);
		
		if (tmp <= maxWidth) {
			width = tmp;
		} else {
			SetClickedButtonTitleToTextbox(WIDTH_TEXTBOX_ID, maxWidth);
		}
	}

	// handle height-textbox
	if (LOWORD(param) == HEIGHT_TEXTBOX_ID) {
		// get text, convert to int
		GetDlgItemText(mainHandle, HEIGHT_TEXTBOX_ID, buf, MAX_CHARS);
		tmp = _tstoi(buf);
		
		if (tmp <= maxHeight) {
			height = tmp;
		} else {
			SetClickedButtonTitleToTextbox(HEIGHT_TEXTBOX_ID, maxHeight);
		}
	}
}