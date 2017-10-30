#include "stdafx.h"
#include "Painter.h"

const int MAP_WIDTH = 32;
const int MAP_HEIGHT = 14;

const int BLOCK_WIDTH = 25;
const int BLOCK_HEIGHT = 25;

Painter::Painter() { }

Painter::~Painter() { }

void Painter::drawWorld(HDC hdc) {
	Graphics* graphics = new Graphics(hdc);

	drawMap(graphics);
}

void Painter::drawMap(Graphics* graphics) {
	char** map = this->getMap();

	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			char map_piece = map[y][x];
			if (map_piece == '#') {
				drawWall(x, y, graphics);
			} else if (map_piece == 'P') {
				drapPacman(x, y, graphics);
			} else if (map_piece == 'G') {
				drapGhost(x, y, graphics);
			}
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

	x = x * BLOCK_WIDTH;
	y = y * BLOCK_HEIGHT;

	graphics->FillRectangle(&brush, x, y, BLOCK_WIDTH, BLOCK_HEIGHT);
}

char ** Painter::getMap() {
	static char** map;

	if (map == nullptr) {

		char map_template[MAP_HEIGHT][MAP_WIDTH] = {
			"###############################",
			"#      G G G G                #",
			"### ################ ###### ###",
			"#   #      #########      # ###",
			"# # #### # ##        #### # # #",
			"# #      # ## ######    # # # #",
			"# #### ### ## #  P   ## # # # #",
			"# #           ##### ##### ### #",
			"# ###### ####       ##        #",
			"# #  ### ######### ####### ####",
			"# # ##                        #",
			"# # ## ############### ########",
			"#                             #",
			"###############################"
		};


		map = new char*[MAP_HEIGHT];
		for (int i = 0; i < MAP_HEIGHT; i++) {
			map[i] = new char[MAP_WIDTH];
			for (int j = 0; j < MAP_WIDTH; j++) {
				map[i][j] = map_template[i][j];
			}
		}
	}

	return map;
}
