#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QPainter>

#include "game.h"

static const double BLOCK_SCALE = 30;
static const double BLOCK_WIDTH = 2 * BLOCK_SCALE;
static const double BLOCK_HEIGHT = 2 * BLOCK_SCALE;

class RenderArea : public QWidget {
    Q_OBJECT

public:
    enum Shape { Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
                 Chord, Pie, Path, Text, Pixmap };

    RenderArea(QWidget *parent = 0);
    QSize sizeHint() const override;

public slots:
    void setShape(Shape shape);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    int** getCharacterCoordinates();
    char** getMap();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int getCharacterIndexByCoordinates(int x, int y, int** character_coordinates);

    void drawWorld(char** map, int** character_coordinates, QPainter& painter);
    void drawGameOverScreen(QPainter& painter);
    void drawWinScreen(QPainter& painter);
    void drawWall(double x, double y, QPainter& painter);
    void drawGhost(double x, double y, QPainter& painter);
    void drawPacman(double x, double y, QPainter& painter);
    void drawFood(double x, double y, QPainter& painter);
    void _drawRectangle(int x, int y, QPainter& painter);

    Shape shape;
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    QPixmap pixmap;
};

#endif // RENDERAREA_H
