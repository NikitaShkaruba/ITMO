#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;
QT_END_NAMESPACE

class RenderArea;

class Window : public QWidget {
    Q_OBJECT

public:
    Window();

private:
    RenderArea *renderArea;
};

#endif // WINDOW_H
