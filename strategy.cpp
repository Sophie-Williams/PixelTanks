#include "strategy.h"



Strategy::Strategy(){
    fuel = defaultFuel;
    moveFuel = defaultMoveFuel *(80+rand()%40)/100;
    damageFuel = defaultDamageFuel*(80+rand()%40)/100;
    waitFuel = defaultWaitFuel*(80+rand()%40)/100;
    shotFuel = defaultShotFuel*(80+rand()%40)/100;
    deathFuel = defaultDeathFuel*(80+rand()%40)/100;
}

Strategy::~Strategy(){}

Move Strategy::GetMove(){
    fuel-=waitFuel;
    if(move.GetAttack()!=WAIT)
        fuel-= shotFuel;
    if(move.GetDirection()!=NONE)
        fuel-= moveFuel;
    return move;
}

void Strategy::SetMove(Move m){
    move = m;
}

bool Strategy::NeedsReset(){
    return (fuel<=0);
}
