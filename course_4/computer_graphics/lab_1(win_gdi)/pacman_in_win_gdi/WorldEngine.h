#pragma once

#include <windows.h>

const int MAP_WIDTH = 32;
const int MAP_HEIGHT = 14;
const int BLOCK_WIDTH = 25;
const int BLOCK_HEIGHT = 25;
const int HORIZONTAL_BLOCKS_AMOUNT = MAP_WIDTH * BLOCK_WIDTH;
const int VERTICAL_BLOCKS_AMOUNT = MAP_HEIGHT * BLOCK_HEIGHT;

const int CHARACTERS_AMOUNT = 1 + 4;

const int PLAYER_DIRECTION_INDEX = 0;

class WorldEngine {
public:
	WorldEngine();
	~WorldEngine();

	void tick();
	void changeDirection(int direction);

	char** getMap();
	int** getCharacterCoordinates();

private:
	int** character_coordinates;
	int* directions;
	char** map;
};

