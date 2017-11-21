#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {
    shape = Polygon;
    pixmap.load(":/images/qt-logo.png");

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::sizeHint() const {
    return QSize(400, 200);
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

    painter.save();

    painter.translate(100, 0);
    QRect rect(10, 20, 80, 60);
    painter.drawLine(rect.bottomLeft(), rect.topRight());

    painter.restore();
}
