#ifndef MOVE_H
#define MOVE_H

#include "QPoint"

#include "helper.h"

class Move
{
protected:
    QPoint position;
    AttackType attack;
    Direction direction;
public:
    Move(QPoint p = QPoint(0,0),AttackType a = WAIT,Direction = NONE);
    void SetAttackType(AttackType);
    void SetDirection(Direction);
    Direction GetDirection();
    AttackType GetAttack();
    QPoint GetPosition();
};

#endif // MOVE_H
