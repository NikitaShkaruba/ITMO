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
	void drawMap(Graphics* graphics);
	void drawWall(int x, int y, Graphics* graphics);
	void drapGhost(int x, int y, Graphics* graphics);
	void drapPacman(int x, int y, Graphics* graphics);
	void drawRectangle(int x, int y, Color color, Graphics* graphics);

	char** getMap();
};

