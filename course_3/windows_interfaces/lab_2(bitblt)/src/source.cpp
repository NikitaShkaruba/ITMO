#include<windows.h>
#include <time.h>
#include <stdio.h>
#include <iostream> 
#include <fstream>

// Human readable signals for window action handlers
#define OPEN 1
#define APPLY_BITBLT 2
#define APPLY_SETPIXEL 3
#define APPLY_DOUBLE_BLUE_CHANNEL 4
#define START_TESTS 5

// Prototypes for functions below
LPCTSTR getFileNameFromDIalog();
int saveBitmap(HDC hdc, HBITMAP bm, int width, int height);
LRESULT CALLBACK handleWindowEvents(HWND, UINT, WPARAM, LPARAM);
void applySetPixel(HWND hwnd, HBITMAP hBitmap);
void applyBitBlt(HWND hWnd, HBITMAP hBitmap);
void applyDoubleBlueChannel(HWND hWnd, HBITMAP hBitmap);
void runTests(HWND hwnd);

// Just global variables to be accessed from everywhere - It's not my code :) I just do the neccessary refactoring
bool isBitmapLoaded = false;
HBITMAP hBitmap;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;  
	WNDCLASS WndClass;
	MSG Msg;
	wchar_t szClassName[] = L"Lab1";

	// Set window attributes
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = handleWindowEvents;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = L"Menu";
	WndClass.lpszClassName = szClassName;

	// Register window class
	if (!RegisterClass(&WndClass)) {
		MessageBox(NULL, L"Cannot register class", L"Error", MB_OK);
		return 0;
	}

	// Create window
	hWnd = CreateWindow(szClassName, L"Image",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	HMENU MainMenu = CreateMenu();
	AppendMenu(MainMenu, MF_STRING, OPEN, TEXT("Open blt file"));
	AppendMenu(MainMenu, MF_STRING, APPLY_BITBLT, TEXT("Change color by BitBlt"));
	AppendMenu(MainMenu, MF_STRING, APPLY_SETPIXEL, TEXT("GetPixel"));
	AppendMenu(MainMenu, MF_STRING, APPLY_DOUBLE_BLUE_CHANNEL, TEXT("Double blue channel"));
	AppendMenu(MainMenu, MF_STRING, START_TESTS, TEXT("Run tests"));
	SetMenu(hWnd, MainMenu);

	if (!hWnd) {
		MessageBox(NULL, L"Cannot create window", L"Error", MB_OK);
		return 0;
	}

	// Show window, start handling his messages
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&Msg, NULL, 0, 0)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	} 

	return Msg.wParam;
}

LRESULT CALLBACK handleWindowEvents(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_PAINT: {
			BITMAP bm;
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hwnd, &ps);

			HDC hCompatibleDC = CreateCompatibleDC(hDC);
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);
			GetObject(hBitmap, sizeof(bm), &bm);
			BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);
			SelectObject(hCompatibleDC, hOldBitmap);
			DeleteDC(hCompatibleDC);

			EndPaint(hwnd, &ps);
			break;
		}
		case WM_COMMAND: {
			if (LOWORD(wParam) == OPEN) {
				LPCTSTR fileName = getFileNameFromDIalog();
				hBitmap = (HBITMAP)LoadImage(0, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				InvalidateRect(hwnd, NULL, TRUE);
				isBitmapLoaded = true;
			}
			if (LOWORD(wParam) == APPLY_BITBLT) {
				if (!isBitmapLoaded) {
					break;
				}
				applyBitBlt(hwnd, hBitmap);
			}
			if (LOWORD(wParam) == APPLY_SETPIXEL) {
				if (!isBitmapLoaded) {
					break;
				}
				applySetPixel(hwnd, hBitmap);
			}
			if (LOWORD(wParam) == APPLY_DOUBLE_BLUE_CHANNEL) {
				applyDoubleBlueChannel(hwnd, hBitmap);
			}
			if (LOWORD(wParam) == START_TESTS) {
				runTests(hwnd);
			}
			break;
		}
		default: {
			return DefWindowProc(hwnd, message, wParam, lParam);
			break;
		}
	}
	return 0;
}

void runTests(HWND hwnd) {
	HBITMAP cpy;
	time_t start_time;
	time_t stats[20];
	for (int type = 0; type<2; type++){
		printf(type ? "pixel:  " : "bitblt: ");
		for (int i = 1; i <= 10; i++){
			cpy = (HBITMAP)CopyImage(hBitmap, IMAGE_BITMAP, i * 100, i * 100, 0);
			start_time = time(NULL);
			switch (type){
			case 0:
				applyBitBlt(hwnd, cpy);
				break;
			case 1:
				applySetPixel(hwnd, cpy);
				break;
			}
			stats[type * 10 + (i - 1)] = time(NULL) - start_time;


			printf("%02d\t", stats[type * 10 + (i - 1)]);
			DeleteObject(cpy);
		}
		printf("\n");
	}
}

void applyBitBlt(HWND hwnd, HBITMAP hBitmap) {
	BITMAP bm;
	HDC hCompatibleDC = CreateCompatibleDC(NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);

	GetObject(hBitmap, sizeof(bm), &bm);
	SelectObject(hCompatibleDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hCompatibleDC, RGB(255, 0, 0));
	BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, MERGECOPY);
	saveBitmap(hCompatibleDC, hBitmap, bm.bmWidth, bm.bmHeight);
	InvalidateRect(hwnd, NULL, TRUE);

	SelectObject(hCompatibleDC, hOldBitmap);
	DeleteDC(hCompatibleDC);
}

void applySetPixel(HWND hwnd, HBITMAP hBitmap) {
	BITMAP bitmap;
	GetObject(hBitmap, sizeof(bitmap), &bitmap);
	HDC hCompatibleDC = CreateCompatibleDC(NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);

	for (int i = 0; i < bitmap.bmWidth; i++) {
		for (int j = 0; j < bitmap.bmHeight; j++) {
			SetPixel(hCompatibleDC, i, j, GetPixel(hCompatibleDC, i, j) | 0x00FF00);
		}
	}

	SelectObject(hCompatibleDC, hOldBitmap);
	saveBitmap(hCompatibleDC, hBitmap, bitmap.bmWidth, bitmap.bmHeight);
	InvalidateRect(hwnd, NULL, TRUE);
	DeleteDC(hCompatibleDC);
	DeleteObject(hOldBitmap);
}

void applyDoubleBlueChannel(HWND hwnd, HBITMAP hBitmap) {
	BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);
    HDC hDCMem = CreateCompatibleDC(NULL);
    HGDIOBJ oldBitmap = SelectObject(hDCMem, hBitmap);
    WORD cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
    DWORD biSizeImage = ((bmp.bmWidth * cClrBits + 31) & ~31) / 8 * bmp.bmHeight;
    BITMAPINFO bmi = { 0 };

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = bmp.bmWidth;
    bmi.bmiHeader.biHeight = bmp.bmHeight;
    bmi.bmiHeader.biPlanes = bmp.bmPlanes;
    bmi.bmiHeader.biBitCount = bmp.bmBitsPixel;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = biSizeImage;
    bmi.bmiHeader.biClrImportant = 0;

    LPBYTE lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, biSizeImage); // memory pointer
    GetDIBits(hDCMem, hBitmap, 0, bmp.bmHeight, lpBits, &bmi, DIB_RGB_COLORS);
    WORD buf;

    for (long i = 0; i < bmp.bmWidth * bmp.bmHeight * 3; i += 3) {
        buf = lpBits[i];
        buf <<= 1;

        if (buf > 255) {
            buf = 255;
		}
        lpBits[i] = buf;
    }

    SetDIBits(hDCMem, hBitmap, 0, bmp.bmHeight, lpBits, &bmi, DIB_RGB_COLORS);
    saveBitmap(hDCMem, hBitmap, bmp.bmWidth, bmp.bmHeight);

    SelectObject(hDCMem, oldBitmap);

    GlobalFree((HGLOBAL)lpBits);
    DeleteDC(hDCMem);
    DeleteObject(oldBitmap);
    InvalidateRect(hwnd, NULL, TRUE);
}

LPCTSTR getFileNameFromDIalog() {
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = new WCHAR[1000];
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 1000;
	ofn.lpstrFilter = L"BMP\0*.bmp\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);

	return ofn.lpstrFile;
}

int saveBitmap(HDC hdc, HBITMAP hbm, int width, int height) {
	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmpSize = ((width * bi.biBitCount + 31) / 32) * 4 * height;
	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	char *lpbitmap = (char *)GlobalLock(hDIB);

	GetDIBits(hdc, hbm, 0,
		(UINT)height,
		lpbitmap,
		(BITMAPINFO *)&bi, DIB_RGB_COLORS);

	HANDLE hFile = CreateFile(L"C:/Users/shnic_000/Desktop/result.bmp",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
	bmfHeader.bfSize = dwSizeofDIB;
	bmfHeader.bfType = 0x4D42;

	DWORD dwBytesWritten = 0;
	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

	//Unlock and Free the DIB from the heap
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	//Close the handle for the file that was created
	CloseHandle(hFile);

	return 0;
}