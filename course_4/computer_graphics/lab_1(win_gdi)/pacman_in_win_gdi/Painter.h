#pragma once

#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;

class Painter {
public:
	Painter();
	~Painter();

	void drawWorld(HDC hdc);

private:
};

