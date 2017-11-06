#pragma once

#include "include.h"

const int MAP_WIDTH = 32;
const int MAP_HEIGHT = 14;
const int HORIZONTAL_BLOCKS_AMOUNT = MAP_WIDTH * BLOCK_WIDTH;
const int VERTICAL_BLOCKS_AMOUNT = MAP_HEIGHT * BLOCK_HEIGHT;

const int CHARACTERS_AMOUNT = 1 + 4;
const int PACMAN_CHARACTER_INDEX = 0;

const int KEY_UP = 1;
const int KEY_DOWN = 2;
const int KEY_LEFT = 3;
const int KEY_RIGHT = 4;

class WorldEngine {
public:
  WorldEngine();
  ~WorldEngine();

  void tick();
  void changeDirection(int character_index, int direction);
  bool hasGhostCollisions(int character_index);

  char** getMap();
  int** getCharacterCoordinates();
  void setCharacterCoordinates(int character_index, int x, int y);
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
