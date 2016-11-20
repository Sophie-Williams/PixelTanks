#ifndef ATTACK_H
#define ATTACK_H

enum AttackType{
    WAIT = 0,
    SIMPLE = 1,
    FREEZING = 2,
    WALLING = 3
};

class Attack
{
    int maxDelay;
    int curentDelay;
    int freeze;
    int damage;
    int length;
    int speed;
    AttackType type;
public:
    Attack(int d = 100,int f = 0,int dm = 40,int l = 100,int s = 2,AttackType t = WAIT);
    int GetSpeed()const{return speed;}
    int GetDamage()const{return damage;}
    AttackType GetType()const{return type;}
    int GetLength()const{return length;}
    int GetFreeze()const{return freeze;}
    int GetDelay()const {return maxDelay;}
};

#endif // ATTACK_H
