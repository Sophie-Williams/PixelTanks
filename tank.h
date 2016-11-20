#ifndef TANK_H
#define TANK_H

#include <QPoint>
#include <QColor>

#include "strategy.h"
#include "object.h"
//#include "bullet.h"
#include "attack.h"

#include <string>
using std::string;

class Tank:public Object
{
    Strategy *strategy;
    int delay;
    int shotDelay;
    //int team;
    int points;
    int healthPoints;
    Direction direction;
    QColor color;
    QColor oldColor;
    QString name;
    int respawnDelay;
    int attackDelay[4];

public:
    Tank(
            QPoint p = QPoint(0,0),
            Strategy *s = NULL,
            Direction d = UP,
            QColor c = Qt::black,
            int h = defaultHealthPoints,
            QString na = "No name");
    virtual ~Tank();
    Direction GetDirection();
    int GetDelay();
    QColor GetColor();
   // void GetTeam();
    Strategy* GetStrategy(){return strategy;}
    Move GetMove(World*);
    void SetMove(Move);
    void SetStrategy(Strategy *s);
    void SetDirection(Direction);
    void SetDelay(int);
    void SetColor(QColor c);


    ObjectType GetObjectType();

  //  Bullet* Procces();
    void Display(QPainter*);
    void erase();
    void TakeDamage(int);
   // QPoint GetPosition();
    bool IsAlive();
    bool Respawn();
    void SetName(QString s){name = s;}
    int GetPoints(){return points;}
    void AddPoints(int p);
    QString GetName(){return name;}
    QString GetInfo();
};

#endif // TANK_H
