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
    int team;
    int points;
    int healthPoints;
    Direction direction;
    QColor color;
    bool alive;
    QString name;

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
    void GetTeam();
    Move GetMove(World*);

    void SetMove(Move);
    void SetStrategy(Strategy *s);
    void SetDirection(Direction);
    void SetDelay(int);
    void SetColor(QColor c){color = c;}


    ObjectType GetObjectType();

  //  Bullet* Procces();
    void Display(QPainter*);
    void erase();
    bool IsAlive(){return alive;}
    void TakeDamage(int);
   // QPoint GetPosition();

    void SetName(QString s){name = s;}
    int GetPoints(){return points;}
    void AddPoints(int p){points+=p;}
    QString GetName(){return name;}
    QString GetInfo();
};

#endif // TANK_H
