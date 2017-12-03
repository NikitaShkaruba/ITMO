#pragma once
#include "include.h"

using namespace std;

static const double BLOCK_SCALE = 0.2;
static const double BLOCK_WIDTH = 1 * BLOCK_SCALE;
static const double BLOCK_HEIGHT = 1 * BLOCK_SCALE;
static const double BLOCK_LENGTH = 0.5 * BLOCK_SCALE;

class Painter {
public:
  Painter();
  ~Painter();

  void drawWorld(char** map, int** character_coordinates);
  void drawGameOverScreen();
  void drawWinScreen();

  GLuint main_vertex_buffer; // Create a variable to hold the VBO identifier
  GLuint main_colours_buffer;
  vector<float> vertices;
  vector<float> colors;

private:
  int getCharacterIndexByCoordinates(int x, int y, int** character_coordinates);

  void drawWall(double x, double y);
  void drawGhost(double x, double y);
  void drawPacman(double x, double y);
  void drawFood(double x, double y);

  void drawRectangle(double x, double y);
  void _drawRectangleInnerSide(double x, double y);
  void _drawRectangleTopSide(double x, double y);
  void _drawRectangleRightSide(double x, double y);

  void drawSmallRectangle(double x, double y);
  void _drawSmallRectangleInnerSide(double x, double y);
  void _drawSmallRectangleTopSide(double x, double y);
  void _drawSmallRectangleRightSide(double x, double y);

  void pushPointToVector(float x, float y, float z);
};
