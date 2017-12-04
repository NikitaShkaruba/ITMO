#ifndef GAME_H
#define GAME_H

#include "renderarea.h"

const int MAP_WIDTH = 32;
const int MAP_HEIGHT = 14;
const int HORIZONTAL_BLOCKS_AMOUNT = MAP_WIDTH * 100; // BLOCK_WIDTH;
const int VERTICAL_BLOCKS_AMOUNT = MAP_HEIGHT * 100; // BLOCK_HEIGHT;

const int CHARACTERS_AMOUNT = 1 + 4;
const int PACMAN_CHARACTER_INDEX = 0;

class Game {

public:
    Game();

    char** getMap();
    int** getCharacterCoordinates();
private:
    int** character_coordinates;
    int* character_directions;
    int* pressed_keys;
    char** map;

    bool is_game_over;
    int apples_left;
};

#endif // GAME_H
