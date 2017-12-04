//
// Created by Nikita Shkaruba on 06/11/2017.
//

#include "include/include.h"

void Painter::drawWall(double x, double y) {
  x = x * BLOCK_SCALE;
  y = y * BLOCK_SCALE;

  drawRectangle(x, y);
}

Painter::Painter() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

  // Render a color-cube consisting of 6 quads with different colors
  glLoadIdentity();                 // Reset the model-view matrix
  glTranslatef(-3, -1, -7.0f);  // Move right and into the screen
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
  x = x * BLOCK_SCALE;
  y = y * BLOCK_SCALE;

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 0.0, 1.0);
  glRectd(x, y, x + BLOCK_WIDTH , y  + BLOCK_HEIGHT);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glRectd(x, y, x + BLOCK_WIDTH , y  + BLOCK_HEIGHT);

  // Top side
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glVertex3d(x, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_LENGTH + BLOCK_WIDTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_LENGTH + BLOCK_WIDTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glEnd();

  // Right side
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y, 0);
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y, 0);
  glEnd();
}

void Painter::drawPacman(double x, double y) {
  x = x * BLOCK_SCALE;
  y = y * BLOCK_SCALE;

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 1.0, 0.0);
  glRectd(x, y, x + BLOCK_WIDTH , y  + BLOCK_HEIGHT);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glRectd(x, y, x + BLOCK_WIDTH , y  + BLOCK_HEIGHT);

  // Top side
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_LENGTH + BLOCK_WIDTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_LENGTH + BLOCK_WIDTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glEnd();

  // Right side
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y, 0);
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y, 0);
  glEnd();
}

Painter::~Painter() = default;

void Painter::drawFood(double x, double y) {
  x = x * BLOCK_SCALE + BLOCK_WIDTH / 2;
  y = y * BLOCK_SCALE + BLOCK_WIDTH / 3;

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(0.0, 1.0, 0.0);
  glRectd(x, y, x + BLOCK_WIDTH / 3, y  + BLOCK_HEIGHT / 3);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glRectd(x, y, x + BLOCK_WIDTH / 3, y  + BLOCK_HEIGHT / 3);

  // Top side
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x, y + BLOCK_HEIGHT / 3, 0);
  glVertex3d(x + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);
  glVertex3d(x + BLOCK_LENGTH / 3 + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);
  glVertex3d(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0);
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x, y + BLOCK_HEIGHT / 3, 0);
  glVertex3d(x + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);
  glVertex3d(x + BLOCK_LENGTH / 3 + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);
  glVertex3d(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0);
  glEnd();

  // Right side
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0);
  glVertex3d(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);
  glVertex3d(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_LENGTH / 3, 0);
  glVertex3d(x + BLOCK_WIDTH / 3, y, 0);
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x + BLOCK_WIDTH / 3, y + BLOCK_HEIGHT / 3, 0);
  glVertex3d(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_HEIGHT / 3 + BLOCK_LENGTH / 3, 0);
  glVertex3d(x + BLOCK_WIDTH / 3 + BLOCK_LENGTH / 3, y + BLOCK_LENGTH / 3, 0);
  glVertex3d(x + BLOCK_WIDTH / 3, y, 0);
  glEnd();
}

void Painter::drawRectangle(double x, double y) {
  // Inner side
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 0.0, 0.0);
  glRectd(x, y, x + BLOCK_WIDTH , y  + BLOCK_HEIGHT);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glRectd(x, y, x + BLOCK_WIDTH , y  + BLOCK_HEIGHT);

  // Top side
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_LENGTH + BLOCK_WIDTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_LENGTH + BLOCK_WIDTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glEnd();

  // Right side
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y, 0);
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3d(x + BLOCK_WIDTH, y + BLOCK_HEIGHT, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_HEIGHT + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH + BLOCK_LENGTH, y + BLOCK_LENGTH, 0);
  glVertex3d(x + BLOCK_WIDTH, y, 0);
  glEnd();
}

int Painter::getCharacterIndexByCoordinates(int x, int y, int** character_coordinates) {
  for (int i = 0; i < CHARACTERS_AMOUNT; i++) {
    if (x == character_coordinates[i][0] && y == character_coordinates[i][1]) {
      return i;
    }
  }

  return -1;
}
