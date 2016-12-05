#include <QApplication>

#include <ctime>

#include "game.h"

#include <omp.h>


int main(int argc, char *argv[])
{
    srand(time(0));
#pragma omp parallel{
    QApplication a(argc, argv);
    Game w;
    w.show();
    w.initTimer();
    return a.exec();
}
}
