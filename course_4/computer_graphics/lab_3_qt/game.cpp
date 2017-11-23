#include "game.h"

Game::Game() {
    char map_template[MAP_HEIGHT][MAP_WIDTH] = {
        "###############################",
        "#P                            #",
        "# # ################ ###### ###",
        "#   #      #########      # ###",
        "# # #### # ##    G   #### # # #",
        "# #      # ## ######    # # # #",
        "# #### ### ## #  G   ## # # #G#",
        "# #           ##### ##### ### #",
        "# ###### ####       ##        #",
        "# #  ### ######### ####### ####",
        "# # ##                        #",
        "# # ## ############### ########",
        "#                  G          #",
        "###############################"
    };

    pressed_keys = new int[4];
    for (int i = 0; i < 4; i++) {
      pressed_keys[i] = 0;
    }

    character_directions = new int[CHARACTERS_AMOUNT];
    character_coordinates = new int*[CHARACTERS_AMOUNT];
    for (int i = 0; i < CHARACTERS_AMOUNT; i++) {
      character_directions[i] = 0;
      character_coordinates[i] = new int[2];
    }


    int current_ghost_index = 1;
    apples_left = 0;
    map = new char*[MAP_HEIGHT];
    for (int y = 0; y < MAP_HEIGHT; y++) {
      map[y] = new char[MAP_WIDTH];
      for (int x = 0; x < MAP_WIDTH; x++) {
        map[y][x] = map_template[y][x];

        if (map[y][x] == 'P') {
          character_coordinates[0][0] = x;
          character_coordinates[0][1] = y;
        } else if (map[y][x] == 'G') {
          character_coordinates[current_ghost_index][0] = x;
          character_coordinates[current_ghost_index][1] = y;
          current_ghost_index++;
        } else if (map[y][x] == ' ') {
          apples_left++;
        }
      }
    }

    is_game_over = false;
}

char** Game::getMap() {
  return map;
}

int ** Game::getCharacterCoordinates() {
  return character_coordinates;
}
