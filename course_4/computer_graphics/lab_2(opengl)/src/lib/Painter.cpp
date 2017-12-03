#include "include/include.h"

void Painter::drawWall(double x, double y) {
  drawRectangle(x, y);
}

Painter::Painter() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

  // Render a color-cube consisting of 6 quads with different colors
  glLoadIdentity();                 // Reset the model-view matrix
  glTranslatef(-3, -1, -7.0f);  // Move right and into the screen
}

Painter::~Painter() = default;

void Painter::pushPointToVector(float x, float y, float z) {
  vertices.push_back(x);
  vertices.push_back(y);
  vertices.push_back(z);
}

void Painter::drawWorld(char** map, int** character_coordinates) {
  vertices.clear();

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

  glVertexPointer(3, GL_FLOAT, 0, NULL);                              // Establish its 3 coordinates per vertex with zero stride in this array; necessary here
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);  // Upload vertex data to the video device
  glBindBuffer(GL_ARRAY_BUFFER, main_vertex_buffer);                  // Make the new VBO active. Repeat here incase changed since initialisation

  glEnableClientState(GL_VERTEX_ARRAY);                               // Establish array contains vertices (not normals, colours, texture coords etc)
  glDrawArrays(GL_LINES, 0, vertices.size() / 3);    // Actually draw the triangle, giving the number of vertices provided
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
  drawRectangle(x, y);
}

void Painter::drawPacman(double x, double y) {
  drawRectangle(x, y);
}

void Painter::drawFood(double x, double y) {
  drawSmallRectangle(x, y);
}

void Painter::drawRectangle(double x, double y) {
  x = x * BLOCK_SCALE;
  y = y * BLOCK_SCALE;

  _drawRectangleInnerSide(x, y);
  _drawRectangleTopSide(x, y);
  _drawRectangleRightSide(x, y);
}

void Painter::_drawRectangleRightSide(double x, double y) {
  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  pushPointToVector(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);

  pushPointToVector(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  pushPointToVector(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_LENGTH, 0);

  pushPointToVector(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_LENGTH, 0);
  pushPointToVector(x + BLOCK_WIDTH, y, 0);

  pushPointToVector(x + BLOCK_WIDTH, y, 0);
  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
}

void Painter::_drawRectangleTopSide(double x, double y) {
  pushPointToVector(x, y + BLOCK_HEIGHT, 0);
  pushPointToVector(x + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);

  pushPointToVector(x + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  pushPointToVector(x + BLOCK_LENGTH + BLOCK_WIDTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);

  pushPointToVector(x + BLOCK_LENGTH + BLOCK_WIDTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);

  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  pushPointToVector(x, y + BLOCK_HEIGHT, 0);
}

void Painter::_drawRectangleInnerSide(double x, double y) {
  pushPointToVector(x, y, 0);
  pushPointToVector(x, y + BLOCK_HEIGHT, 0);

  pushPointToVector(x, y + BLOCK_HEIGHT, 0);
  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);

  pushPointToVector(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  pushPointToVector(x + BLOCK_WIDTH, y, 0);

  pushPointToVector(x + BLOCK_WIDTH, y, 0);
  pushPointToVector(x, y, 0);
}

int Painter::getCharacterIndexByCoordinates(int x, int y, int** character_coordinates) {
  for (int i = 0; i < CHARACTERS_AMOUNT; i++) {
    if (x == character_coordinates[i][0] && y == character_coordinates[i][1]) {
      return i;
    }
  }

  return -1;
}

void Painter::drawSmallRectangle(double x, double y) {
  x = x * BLOCK_SCALE + BLOCK_WIDTH / 3;
  y = y * BLOCK_SCALE  + BLOCK_HEIGHT / 3;

  _drawSmallRectangleInnerSide(x, y);
  _drawSmallRectangleTopSide(x, y);
  _drawSmallRectangleRightSide(x, y);
}

void Painter::_drawSmallRectangleInnerSide(double x, double y) {
  pushPointToVector(x, y, 0);
  pushPointToVector(x, y + BLOCK_HEIGHT / 3, 0);

  pushPointToVector(x, y + BLOCK_HEIGHT / 3, 0);
  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0);

  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0);
  pushPointToVector(x + BLOCK_WIDTH / 3, y, 0);

  pushPointToVector(x + BLOCK_WIDTH / 3, y, 0);
  pushPointToVector(x, y, 0);
}

void Painter::_drawSmallRectangleTopSide(double x, double y) {
  pushPointToVector(x, y + BLOCK_HEIGHT / 3, 0);
  pushPointToVector(x + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);

  pushPointToVector(x + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);
  pushPointToVector(x + BLOCK_LENGTH / 3 + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);

  pushPointToVector(x + BLOCK_LENGTH / 3 + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);
  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0);

  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0);
  pushPointToVector(x, y + BLOCK_HEIGHT / 3, 0);
}

void Painter::_drawSmallRectangleRightSide(double x, double y) {
  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0);
  pushPointToVector(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);

  pushPointToVector(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);
  pushPointToVector(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_LENGTH / 3, 0);

  pushPointToVector(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_LENGTH / 3, 0);
  pushPointToVector(x + BLOCK_WIDTH / 3, y, 0);

  pushPointToVector(x + BLOCK_WIDTH / 3, y, 0);
  pushPointToVector(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0);
}
