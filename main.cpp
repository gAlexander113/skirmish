#include <QApplication>
#include "skirmish.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Skirmish window;

    window.init();
    window.resize(640, 480);
    window.move(100, 100);

    window.show();

    return app.exec();
}
