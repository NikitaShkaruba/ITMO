#include "window.h"
#include "game.h"

#include <QApplication>

Game* game = nullptr;

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(basicdrawing);

    QApplication app(argc, argv);
    Window window;

    window.show();
    return app.exec();
}
