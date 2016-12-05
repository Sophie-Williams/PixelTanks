#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QTimer>

#include<QTableView>

#include <vector>
using std::vector;

#include "world.h"
#include "tank.h"
#include "playerstrategy.h"
#include "paintwidget.h"

namespace Ui {
class Game;
}

class Game : public QMainWindow
{
    Q_OBJECT
    vector< char > keys;

    PaintWidget *widget;

protected:
    void keyPressEvent(QKeyEvent* );

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

    void paintEvent(QPaintEvent *event);

    void initTimer();

private slots:

    void refreshWorld();

    void on_StartGame_clicked();

    void on_WidthBox_valueChanged(int arg1);

    void on_HeigthBox_valueChanged(int arg1);

    void on_AddNeuroBots_clicked();

    void on_AddSimpleBots_clicked();

private:
    Ui::Game *ui;
    QTableView *leaders;
};

#endif // GAME_H
