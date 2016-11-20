#ifndef CONSTANTS
#define CONSTANTS

#include <vector>
using std::vector;

#include <QPoint>
#include <qcolor.h>

#include "attack.h"


const int moveDelay = 5;
const int turnDelay = 7;
const int cellSize = 22;
const int paintSize = 11;
const int defaultShotDelay = 2;

const int killPoints = 100;

const int worldHeight = 40;
const int worldWidth = 27;

const int botsCount = 20;

const int maxHealth = 1000000;

const int renewInterval = 30;

const int defaultHealthPoints = 600;
const int wallHealthPoints = 2500;

const Attack simpleAttack(10,  0,100,15*cellSize, cellSize/5,  SIMPLE);
const Attack freezeAttack(30, 20, 20,10*cellSize,cellSize/10,FREEZING);
const Attack wallAttck   (50,  0,300, 5*cellSize,cellSize/15, WALLING);

const Attack attacks[4] = {
    Attack(),simpleAttack,freezeAttack,wallAttck
};

const QColor tankColor = Qt::black;
const QColor playerColor = Qt::red;
const QColor frozenColor = Qt::blue;

const QColor backgroundColor = Qt::white;
const QColor wallColor = Qt::gray;
const QColor bulletColor = Qt::green;

const int listX = (worldHeight+2)*cellSize+ 10;
const int listY = 10;

const int shift = 10;

const vector<int> neuroNetConfiguration = {8,10,8};


enum Direction{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    NONE = 4
};

enum ObjectType{
    OBJECT = 0,
    EMPTY = 1,
    WALL = 2,
    TANK = 3
};

QPoint toCellCoordinats(QPoint);
QPoint toSimpleCoordinats(QPoint);
QPoint moveVector(Direction);

#endif // CONSTANTS

