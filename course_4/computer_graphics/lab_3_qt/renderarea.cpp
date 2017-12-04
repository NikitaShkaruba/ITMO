#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {
    shape = Polygon;
    pixmap.load(":/images/qt-logo.png");

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::sizeHint() const {
    return QSize(1800, 422);
}

void RenderArea::setShape(Shape shape) {
    this->shape = shape;
    update();
}

void RenderArea::setPen(const QPen &pen) {
    this->pen = pen;
    update();
}

void RenderArea::setBrush(const QBrush &brush) {
    this->brush = brush;
    update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */) {
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.translate(31, 31);

    drawWorld(getMap(), getCharacterCoordinates(), painter);
}

void RenderArea::_drawRectangle(int x, int y, QPainter& painter) {
    painter.save();

    x = x * BLOCK_SCALE;
    y = y * BLOCK_SCALE;

    painter.translate(x, y);
    QRect rect(-BLOCK_WIDTH / 2, -BLOCK_HEIGHT / 2, BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2);
    painter.drawRect(rect);

    painter.restore();
}

void RenderArea::drawWall(double x, double y, QPainter& painter) {
  _drawRectangle(x, y, painter);
}

void RenderArea::drawWorld(char** map, int** character_coordinates, QPainter& painter) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      char map_piece = map[y][x];
      int character_index = getCharacterIndexByCoordinates(x, y, character_coordinates);

      if (character_index >= 0) {
        if (character_index == 0) {
          drawPacman(x, y, painter);
        } else {
          drawGhost(x, y, painter);
        }
      } else if (map_piece == '#') {
        drawWall(x, y, painter);
      } else if (map_piece == ' ') {
        drawFood(x, y, painter);
      } else if (map_piece == '.') {
        // Do nothing. It's eaten
      }
    }
  }
}

void RenderArea::drawGameOverScreen(QPainter& painter) {
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
        drawWall(x, y, painter);
      }
    }
  }
}

void RenderArea::drawWinScreen(QPainter& painter) {
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
        drawWall(x, y, painter);
      }
    }
  }
}

void RenderArea::drawGhost(double x, double y, QPainter& painter) {
  //
}

void RenderArea::drawPacman(double x, double y, QPainter& painter) {
  //
}

void RenderArea::drawFood(double x, double y, QPainter& painter) {
  //
}

int RenderArea::getCharacterIndexByCoordinates(int x, int y, int** character_coordinates) {
  for (int i = 0; i < CHARACTERS_AMOUNT; i++) {
    if (x == character_coordinates[i][0] && y == character_coordinates[i][1]) {
      return i;
    }
  }

  return -1;
}

int** RenderArea::getCharacterCoordinates() {
    int** character_coordinates = new int*[CHARACTERS_AMOUNT];
    for (int i = 0; i < CHARACTERS_AMOUNT; i++) {
      // character_directions[i] = 0;
      character_coordinates[i] = new int[2];
    }

    return character_coordinates;
}

char** RenderArea::getMap() {
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

    char** map = new char*[MAP_HEIGHT];
    for (int y = 0; y < MAP_HEIGHT; y++) {
      map[y] = new char[MAP_WIDTH];
      for (int x = 0; x < MAP_WIDTH; x++) {
        map[y][x] = map_template[y][x];
      }
    }

    return map;
}
