#include "include/include.h"

void Painter::drawWall(double x, double y) {
  drawRectangle(x, y, 0.2, 0.2, 0.2);
}

Painter::Painter() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

  // Render a color-cube consisting of 6 quads with different colors
  glLoadIdentity();                 // Reset the model-view matrix
  glTranslatef(-3, -1, -7.0f);  // Move right and into the screen
}

Painter::~Painter() = default;

void Painter::pushPointToVector(float x, float y, float z, float red, float green, float blue) {
  vertices.push_back(x);
  vertices.push_back(y);
  vertices.push_back(z);

  colors.push_back(red);
  colors.push_back(green);
  colors.push_back(blue);
}

int Painter::getCharacterIndexByCoordinates(int x, int y, int** character_coordinates) {
  for (int i = 0; i < CHARACTERS_AMOUNT; i++) {
    if (x == character_coordinates[i][0] && y == character_coordinates[i][1]) {
      return i;
    }
  }

  return -1;
}

void Painter::drawWorld(char** map, int** character_coordinates) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      char map_piece = map[y][x];
      int character_index = getCharacterIndexByCoordinates(x, y, character_coordinates);

      if (character_index >= 0) {
        if (character_index == 0) {
          drawPacman(x, y);
        } else {
          drawGhost(x, y);
        }
      } else if (map_piece == '#') {
        drawWall(x, y);
      } else if (map_piece == ' ') {
        drawFood(x, y);
      } else if (map_piece == '.') {
        // Do nothing. It's eaten
      }
    }
  }
}

void Painter::drawGameOverScreen() {
  char map[MAP_HEIGHT][MAP_WIDTH] = {
      "###############################",
      "###############################",
      "###############################",
      "###############################",
      "########     ####     #########",
      "######## ### #### ### #########",
      "######## #   #### ### #########",
      "######## ######## ### #########",
      "########     ####     #########",
      "###############################",
      "###############################",
      "###############################",
      "###############################",
      "###############################",
  };

  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      char map_piece = map[y][x];

      if (map_piece == '#') {
        drawWall(x, y);
      }
    }
  }
}

void Painter::drawWinScreen() {
  char map[MAP_HEIGHT][MAP_WIDTH] = {
      "###############################",
      "###############################",
      "###############################",
      "###############################",
      "######   ##   ##  ##   ### ####",
      "#####  # #  # ##  ## #  ## ####",
      "####  ##   ## ##  ## ##  # ####",
      "###  ###  ### ##  ## ###   ####",
      "###############################",
      "###############################",
      "###############################",
      "###############################",
      "###############################",
      "###############################",
  };

  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      char map_piece = map[y][x];

      if (map_piece == '#') {
        drawWall(x, y);
      }
    }
  }
}

void Painter::drawGhost(double x, double y) {
  drawRectangle(x, y, 1, 0, 0);
}

void Painter::drawPacman(double x, double y) {
  drawRectangle(x, y, 1, 1, 0);
}

void Painter::drawFood(double x, double y) {
  drawSmallRectangle(x, y, 0, 0.8, 0);
}

void Painter::drawRectangle(double x, double y, float red, float green, float blue) {
  x = x * BLOCK_SCALE;
  y = y * BLOCK_SCALE;

  _drawRectangleInnerSide(x, y, red, green, blue);
  _drawRectangleTopSide(x, y, red, green, blue);
  _drawRectangleRightSide(x, y, red, green, blue);
}

void Painter::_drawRectangleRightSide(double x, double y, float red, float green, float blue) {
  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_LENGTH, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_LENGTH, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH, y, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH, y, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0, red, green, blue);
}

void Painter::_drawRectangleTopSide(double x, double y, float red, float green, float blue) {
  pushPointToVector(x, y + BLOCK_HEIGHT, 0, red, green, blue);
  pushPointToVector(x + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0, red, green, blue);

  pushPointToVector(x + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0, red, green, blue);
  pushPointToVector(x + BLOCK_LENGTH + BLOCK_WIDTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0, red, green, blue);

  pushPointToVector(x + BLOCK_LENGTH + BLOCK_WIDTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0, red, green, blue);
  pushPointToVector(x, y + BLOCK_HEIGHT, 0, red, green, blue);
}

void Painter::_drawRectangleInnerSide(double x, double y, float red, float green, float blue) {
  pushPointToVector(x, y, 0, red, green, blue);
  pushPointToVector(x, y + BLOCK_HEIGHT, 0, red, green, blue);

  pushPointToVector(x, y + BLOCK_HEIGHT, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH, y, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH, y, 0, red, green, blue);
  pushPointToVector(x, y, 0, red, green, blue);
}

void Painter::drawSmallRectangle(double x, double y, float red, float green, float blue) {
  x = x * BLOCK_SCALE + BLOCK_WIDTH / 3;
  y = y * BLOCK_SCALE  + BLOCK_HEIGHT / 3;

  _drawSmallRectangleInnerSide(x, y, red, green, blue);
  _drawSmallRectangleTopSide(x, y, red, green, blue);
  _drawSmallRectangleRightSide(x, y, red, green, blue);
}

void Painter::_drawSmallRectangleInnerSide(double x, double y, float red, float green, float blue) {
  pushPointToVector(x, y, 0, red, green, blue);
  pushPointToVector(x, y + BLOCK_HEIGHT / 3, 0, red, green, blue);

  pushPointToVector(x, y + BLOCK_HEIGHT / 3, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH / 3, y, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH / 3, y, 0, red, green, blue);
  pushPointToVector(x, y, 0, red, green, blue);
}

void Painter::_drawSmallRectangleTopSide(double x, double y, float red, float green, float blue) {
  pushPointToVector(x, y + BLOCK_HEIGHT / 3, 0, red, green, blue);
  pushPointToVector(x + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0, red, green, blue);

  pushPointToVector(x + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0, red, green, blue);
  pushPointToVector(x + BLOCK_LENGTH / 3 + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0, red, green, blue);

  pushPointToVector(x + BLOCK_LENGTH / 3 + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0, red, green, blue);
  pushPointToVector(x, y + BLOCK_HEIGHT / 3, 0, red, green, blue);
}

void Painter::_drawSmallRectangleRightSide(double x, double y, float red, float green, float blue) {
  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_LENGTH / 3, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_LENGTH / 3, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH / 3, y, 0, red, green, blue);

  pushPointToVector(x + BLOCK_WIDTH / 3, y, 0, red, green, blue);
  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0, red, green, blue);
}
