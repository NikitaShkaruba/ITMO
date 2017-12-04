#include "include/Game.h"

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


Game::~Game() = default;

char** Game::getMap() {
  return map;
}

int ** Game::getCharacterCoordinates() {
  return character_coordinates;
}

bool Game::isGameOver() {
  return is_game_over;
}

bool Game::isPlayerWins() {
  return apples_left == 0;
}

int Game::getRandomDirection(int character_index) {
  int character_x = character_coordinates[character_index][0];
  int character_y = character_coordinates[character_index][1];
  int current_direction = character_directions[character_index];

  vector<int> available_choises = {};

  if (character_y != 0 && map[character_y - 1][character_x] != '#') {
    available_choises.push_back(KEY_UP);
  }
  if (character_y != MAP_HEIGHT - 1 && map[character_y + 1][character_x] != '#') {
    available_choises.push_back(KEY_DOWN);
  }
  if (character_x != 0 && map[character_y][character_x - 1] != '#') {
    available_choises.push_back(KEY_LEFT);
  }
  if (character_x != MAP_WIDTH - 1 && map[character_y][character_x + 1] != '#') {
    available_choises.push_back(KEY_RIGHT);
  }

  if (available_choises.size() != 1) {
    switch (current_direction) {
      case KEY_UP:
        available_choises.erase(remove(available_choises.begin(), available_choises.end(), KEY_DOWN), available_choises.end());
        break;

      case KEY_DOWN:
        available_choises.erase(remove(available_choises.begin(), available_choises.end(), KEY_UP), available_choises.end());
        break;

      case KEY_LEFT:
        available_choises.erase(remove(available_choises.begin(), available_choises.end(), KEY_RIGHT), available_choises.end());
        break;

      case KEY_RIGHT:
        available_choises.erase(remove(available_choises.begin(), available_choises.end(), KEY_LEFT), available_choises.end());
        break;

      default:break;
    }
  }

  int choise_index = static_cast<int>(rand() % available_choises.size());
  return available_choises[choise_index];
}

void Game::tick() {
  for (int character_index = 0; character_index < CHARACTERS_AMOUNT; character_index++) {
    int character_x = character_coordinates[character_index][0];
    int character_y = character_coordinates[character_index][1];

    // change direction if needed
    if (character_index == PACMAN_CHARACTER_INDEX) {
      processPressedKeys(character_index, character_x, character_y);
    } else {
      setGhostDirection(character_index);
    }

    int* character_directions = getCharacterDirections();
    int character_direction = character_directions[character_index];
    switch (character_direction) {
      case KEY_UP:
        if (character_y != MAP_HEIGHT - 1 && map[character_y + 1][character_x] != '#') {
          character_coordinates[character_index][1]++;
        }
        break;

      case KEY_LEFT:
        if (character_x != 0 && map[character_y][character_x - 1] != '#') {
          character_coordinates[character_index][0]--;
        }
        break;

      case KEY_DOWN:
        if (character_y != 0 && map[character_y - 1][character_x] != '#') {
          character_coordinates[character_index][1]--;
        }
        break;

      case KEY_RIGHT:
        if (character_x != MAP_WIDTH - 1 && map[character_y][character_x + 1] != '#') {
          character_coordinates[character_index][0]++;
        }
        break;

      default:
        break;
    }

    if (PlayerHasGhostCollisions(PACMAN_CHARACTER_INDEX)) {
      is_game_over = true;
    }
  }

  int pacman_x = character_coordinates[PACMAN_CHARACTER_INDEX][0];
  int pacman_y = character_coordinates[PACMAN_CHARACTER_INDEX][1];

  if (map[pacman_y][pacman_x] == ' ') {
    map[pacman_y][pacman_x] = '_';
    apples_left--;
  }
}

void Game::setGhostDirection(int character_index) {
  int random_ghost_direction = getRandomDirection(character_index);
  changeDirection(character_index, random_ghost_direction);
}

void Game::processPressedKeys(int character_index, int character_x, int character_y) {
  int* pressed_keys = getPressedKeys();
  for (int i = 0; i < 4; i++) {
        if (pressed_keys[i]) {
          switch (i) {
            case KEY_UP:
              if (character_y != 0 && map[character_y + 1][character_x] != '#') {
                changeDirection(character_index, i);
              }
              break;

            case KEY_LEFT:
              if (character_x != 0 && map[character_y][character_x - 1] != '#') {
                changeDirection(character_index, i);
              }
              break;

            case KEY_DOWN:
              if (character_y != MAP_HEIGHT - 1 && map[character_y - 1][character_x] != '#') {
                changeDirection(character_index, i);
              }
              break;

            case KEY_RIGHT:
              if (character_x != MAP_WIDTH - 1 && map[character_y][character_x + 1] != '#') {
                changeDirection(character_index, i);
              }
              break;

            default:
              break;
          }
          break;
        }
      }
}

void Game::changeDirection(int character_index, int direction) {
  character_directions[character_index] = direction;
}

bool Game::PlayerHasGhostCollisions(int character_index) {
  int pacman_x = character_coordinates[character_index][0];
  int pacman_y = character_coordinates[character_index][1];

  for (int i = 1; i < CHARACTERS_AMOUNT; i++) {
    int character_x = character_coordinates[i][0];
    int character_y = character_coordinates[i][1];

    if (character_x == pacman_x && character_y == pacman_y) {
      return true;
    }
  }

  return false;
}

void Game::setKeyPress(int direction, int value) {
  pressed_keys[direction] = value;
}

int* Game::getCharacterDirections() {
  return character_directions;
}

int* Game::getPressedKeys() {
  return pressed_keys;
}
