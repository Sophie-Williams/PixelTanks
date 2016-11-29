#ifndef BULLET_H
#define BULLET_H

#include <QPoint>

#include "helper.h"
#include "tank.h"
#include "object.h"

class Bullet:public Object
{
   // QPoint position;
    QPoint moveVector;
    Attack attack;
    int way;
    Tank *owner;
public:
    //Bullet();
    Bullet(Tank* t,Attack a,QPoint p,Direction d);
    virtual ~Bullet();

    bool Shift();
    void Display(QPainter* p);
  //  QPoint GetPosition(){return position;}
    void SetPosition(QPoint p){position = p;}
    int GetDamage(){return attack.GetDamage();}
    Tank* GetOwner(){return owner;}
    AttackType GetAttackType(){return attack.GetType();}
    int GetFreeze(){return attack.GetFreeze();}
};

#endif // BULLET_H
