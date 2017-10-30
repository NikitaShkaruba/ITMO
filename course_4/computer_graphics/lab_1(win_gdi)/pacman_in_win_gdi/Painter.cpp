#include "stdafx.h"
#include "Painter.h"
#include "WorldEngine.h"

Painter::Painter() { }

Painter::~Painter() { }

void Painter::drawWorld(HDC hdc, char** map, int** character_coordinates) {
	Graphics* graphics = new Graphics(hdc);

	drawMap(graphics, map);
	drawCharacters(graphics, character_coordinates);
}

void Painter::drawMap(Graphics* graphics, char** map) {
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			char map_piece = map[y][x];

			int piece_x = x * BLOCK_WIDTH;
			int piece_y = y * BLOCK_HEIGHT;

			if (map_piece == '#') {
				drawWall(piece_x, piece_y, graphics);
			}
		}
	}
}

void Painter::drawCharacters(Graphics* graphics, int** character_coordinates) {
	for (int i = 0; i < CHARACTERS_AMOUNT; i++) {
		int character_x = character_coordinates[i][0] * BLOCK_WIDTH;
		int character_y = character_coordinates[i][1] * BLOCK_HEIGHT;
		
		if (i == 0) {
			drapPacman(character_x, character_y, graphics);
		} else {
			drapGhost(character_x, character_y, graphics);
		}
	}
}

void Painter::drawWall(int x, int y, Graphics* graphics) {
	drawRectangle(x, y, Color(0, 0, 0), graphics);
}

void Painter::drapGhost(int x, int y, Graphics * graphics) {
	drawRectangle(x, y, Color(200, 0, 200), graphics);
}

void Painter::drapPacman(int x, int y, Graphics* graphics) {
	drawRectangle(x, y, Color(200, 200, 0), graphics);
}

void Painter::drawRectangle(int x, int y, Color color, Graphics* graphics) {
	SolidBrush brush(color);

	graphics->FillRectangle(&brush, x, y, BLOCK_WIDTH, BLOCK_HEIGHT);
}