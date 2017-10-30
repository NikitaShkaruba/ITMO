#include "stdafx.h"
#include "Painter.h"

Painter::Painter() { }

Painter::~Painter() { }

void Painter::drawWorld(HDC hdc) {
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));

	graphics.DrawLine(&pen, 0, 0, 200, 100);
}