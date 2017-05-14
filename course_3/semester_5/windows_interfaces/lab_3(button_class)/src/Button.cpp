#include "Button.h"

int Button::buttonId = 1000;
int Button::nextButtonY = 160;

Button::Button(HINSTANCE instance, HWND parent, LPCWSTR title, int width, int height) {
	this->height = height;
	this->width = width;
	this->title = title;
	this->nextButtonY += this->height;

	HWND hNewBtn = CreateWindow(L"Button", NULL, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, this->nextButtonY, this->width, this->height, parent, (HMENU)buttonId++, instance, 0);
	SetWindowText(hNewBtn, this->title);
}

Button::Button(HINSTANCE instance, HWND parent) {
	this->height = 20;
	this->width = 70;
	this->title = L"Default";
	this->nextButtonY += this->height;

	HWND hNewBtn = CreateWindow(L"Button", NULL, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, this->nextButtonY, this->width, this->height, parent, (HMENU)buttonId++, instance, 0);
	SetWindowText(hNewBtn, this->title);
}