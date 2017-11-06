#pragma once

#include "include.h"

const int MAP_WIDTH = 32;
const int MAP_HEIGHT = 14;
const int HORIZONTAL_BLOCKS_AMOUNT = MAP_WIDTH * BLOCK_WIDTH;
const int VERTICAL_BLOCKS_AMOUNT = MAP_HEIGHT * BLOCK_HEIGHT;

const int CHARACTERS_AMOUNT = 1 + 4;
const int PACMAN_CHARACTER_INDEX = 0;

const int KEY_UP = 0;
const int KEY_DOWN = 1;
const int KEY_LEFT = 2;
const int KEY_RIGHT = 3;

class Game {
public:
  Game();
  ~Game();

  void tick();
  char** getMap();
  bool isGameOver();
  bool isPlayerWins();

  bool hasGhostCollisions(int character_index);
  int getRandomDirection(int character_index);

  int** getCharacterCoordinates();
  void setCharacterCoordinates(int character_index, int x, int y);
  int* getCharacterDirections();
  void changeDirection(int character_index, int direction);
  void setKeyPress(int direction, int value);
  int* getPressedKeys();

private:

  int** character_coordinates;
  int* character_directions;
  int* pressed_keys;
  char** map;

  bool is_game_over;
  int apples_left;
};
