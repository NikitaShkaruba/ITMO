#include<windows.h>
#include <time.h>
#include <stdio.h>
#include <iostream> 
#include <fstream>

// Human readable signals for 
#define LOAD	1
#define APPLY	2
#define APPLY_GETPIXEL	3
#define START_TESTS	4

// Prototypes for functions below
LPCTSTR OpenFile();
int save_bmp(HDC hdc, HBITMAP bm, int width, int height);
LRESULT CALLBACK handleWindowEvents(HWND, UINT, WPARAM, LPARAM);
void setPixelDisplay(HWND hwnd, HBITMAP hBitmap);
void setBlt(HWND hWnd, HBITMAP hBitmap);
void execute(HWND hwnd);

// Just global variables to be accessed from everywhere
bool isLoaded = false;
LPCTSTR fileName;
HDC hDC;
PAINTSTRUCT PaintStruct;
HDC hCompatibleDC;
HANDLE hOldBitmap;
BITMAP Bitmap;
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
	AppendMenu(MainMenu, MF_STRING, LOAD, TEXT("Open blt file"));
	AppendMenu(MainMenu, MF_STRING, APPLY, TEXT("Change color by BitBlt"));
	AppendMenu(MainMenu, MF_STRING, START_TESTS, TEXT("Run tests"));
	AppendMenu(MainMenu, MF_STRING, APPLY_GETPIXEL, TEXT("GetPixel"));
	SetMenu(hWnd, MainMenu);

	if (!hWnd) {
		MessageBox(NULL, L"Cannot create window", L"Error", MB_OK);
		return 0;
	}

	// Show window, append menus and start handling his messages
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
			hDC = BeginPaint(hwnd, &ps);

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
			if (LOWORD(wParam) == LOAD) {
				fileName = OpenFile();
				hBitmap = (HBITMAP)LoadImage(0, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				InvalidateRect(hwnd, NULL, TRUE);
				isLoaded = true;
			}

			if (LOWORD(wParam) == START_TESTS) {
				execute(hwnd);
				break;
			}

			if (LOWORD(wParam) == APPLY) {
				if (!isLoaded) {
					break;
				}
				setBlt(hwnd, hBitmap);
			}

			if (LOWORD(wParam) == APPLY_GETPIXEL) {
				if (!isLoaded) {
					break;
				}
				setPixelDisplay(hwnd, hBitmap);
			}
			break;
		}
	
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
			break;
	}
	return 0;
}

void execute(HWND hwnd) {
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
				setBlt(hwnd, cpy);
				break;
			case 1:
				setPixelDisplay(hwnd, cpy);
				break;
			}
			stats[type * 10 + (i - 1)] = time(NULL) - start_time;


			printf("%02d\t", stats[type * 10 + (i - 1)]);
			DeleteObject(cpy);
		}
		printf("\n");
	}
}

void setBlt(HWND hwnd, HBITMAP hBitmap) {
	BITMAP bm;
	HDC hCompatibleDC = CreateCompatibleDC(NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);

	GetObject(hBitmap, sizeof(bm), &bm);

	SelectObject(hCompatibleDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hCompatibleDC, RGB(255, 0, 0));

	BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, MERGECOPY);
	save_bmp(hCompatibleDC, hBitmap, bm.bmWidth, bm.bmHeight);

	InvalidateRect(hwnd, NULL, TRUE);

	SelectObject(hCompatibleDC, hOldBitmap);
	DeleteDC(hCompatibleDC);
}

void setPixelDisplay(HWND hwnd, HBITMAP hBitmap) {
	BITMAP bm;
	GetObject(hBitmap, sizeof(bm), &bm); //извлекает размеры заданного графического объекта

	HDC hCompatibleDC = CreateCompatibleDC(NULL); //создать контекст памяти, совместимый с контекстом отображения реального устройства вывода
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);  // Выбираем изображение bitmap в контекст памяти

	//BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);

	for (int i = 0; i < bm.bmWidth; i++) {
		for (int j = 0; j < bm.bmHeight; j++) {
			//COLORREF clr = GetPixel(hCompatibleDC, i, j);
			//SetPixel(hCompatibleDC, i, j, RGB(GetRValue(clr), 0, 0));
			SetPixel(hCompatibleDC, i, j,
				GetPixel(hCompatibleDC, i, j) | 0x00FF00);
		}
	}

	SelectObject(hCompatibleDC, hOldBitmap);
	save_bmp(hCompatibleDC, hBitmap, bm.bmWidth, bm.bmHeight);
	InvalidateRect(hwnd, NULL, TRUE);
	DeleteDC(hCompatibleDC);
	DeleteObject(hOldBitmap);
}

LPCTSTR OpenFile(){
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

int save_bmp(HDC hdc, HBITMAP H, int width, int height) {
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

	GetDIBits(hdc, H, 0,
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
	bmfHeader.bfType = 0x4D42; //BM   

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