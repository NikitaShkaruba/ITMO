#pragma once

#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;

class Painter {
public:
	Painter();
	~Painter();

	void drawWorld(HDC hdc, char** map, int** character_coordinates);
	void drawGameOverScreen(HDC hdc);
	void drawWinScreen(HDC hdc);

private:
	void drawMap(Graphics* graphics, char** map);
	void drawCharacters(Graphics* graphics, int** character_coordinates);

	void drawWall(int x, int y, Graphics* graphics);
	void drapGhost(int x, int y, Graphics* graphics);
	void drapPacman(int x, int y, Graphics* graphics);
	void drawFood(int x, int y, Graphics* graphics);
	void drawNothing(int x, int y, Graphics* graphics);

	void drawRectangle(int x, int y, Color color, Graphics* graphics);

	char** getMap();
};

