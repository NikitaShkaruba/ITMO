#pragma once

#include <string>
#include <windows.h>

#define ID_SNEW	1000

using namespace std;

class Button {
public:
	Button::Button(HINSTANCE instance, HWND parent, LPCWSTR title, int width, int height);
	Button::Button(HINSTANCE instance, HWND parent);
private:
	static int buttonId; // Handle id
	static int nextButtonY; // Every button is placed on a window, to prevent collisions, i use this static Y which increments after every constructor call
	int height, width;
	LPCTSTR title;
};