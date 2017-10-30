#pragma once

#include <windows.h>
#include <vector>
#include <algorithm>

const int MAP_WIDTH = 32;
const int MAP_HEIGHT = 14;
const int BLOCK_WIDTH = 25;
const int BLOCK_HEIGHT = 25;
const int HORIZONTAL_BLOCKS_AMOUNT = MAP_WIDTH * BLOCK_WIDTH;
const int VERTICAL_BLOCKS_AMOUNT = MAP_HEIGHT * BLOCK_HEIGHT;

const int CHARACTERS_AMOUNT = 1 + 4;

const int PACMAN_CHARACTER_INDEX = 0;

using namespace std;

class WorldEngine {
public:
	WorldEngine();
	~WorldEngine();

	void tick();
	void changeDirection(int character_index, int direction);
	bool hasGhostCollisions(int character_index);

	char** getMap();
	int** getCharacterCoordinates();
	bool isGameOver();
	bool isPlayerWins();

private:
	int getRandomDirection(int character_index);

	int** character_coordinates;
	int* directions;
	char** map;

	bool is_game_over;
	int apples_left;
};

