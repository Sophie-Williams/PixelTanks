#include "strategy.h"

Strategy::Strategy(){
    fuel = defaultFuel;
    moveFuel = defaultMoveFuel;
    damageFuel = defaultDamageFuel;
    waitFuel = defaultWaitFuel;
    shotFuel = defaultShotFuel;
    deathFuel = defaultDeathFuel;
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
