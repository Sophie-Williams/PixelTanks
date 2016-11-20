#include <QApplication>

#include <ctime>

#include "game.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    Game w;
    w.show();
    w.initTimer();

    return a.exec();
}
