#include "move.h"

Move::Move(QPoint p,AttackType a,Direction d):
    position(p),attack(a),direction(d){}

void Move::SetAttackType(AttackType a){
    attack = a;
}

void Move::SetDirection(Direction d){
    direction = d;
}

AttackType Move::GetAttack(){return attack;}

Direction Move::GetDirection(){return direction;}
