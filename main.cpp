#include <QApplication>

#include <ctime>

#include "game.h"

//#include <omp.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(0));
    Game w;
    w.show();
    w.initTimer();
    return a.exec();
}
