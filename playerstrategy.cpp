#include "playerstrategy.h"

#include <iostream>

PlayerStrategy* PlayerStrategy::singleton;

PlayerStrategy::PlayerStrategy()
{
}

PlayerStrategy::~PlayerStrategy(){
    singleton = NULL;
}

Move PlayerStrategy::CalculateMove(World*,Tank*){
    return move;
}

PlayerStrategy* PlayerStrategy::GetInstance(){
    if (singleton == NULL)
        singleton = new PlayerStrategy();
    return singleton;
}

void PlayerStrategy::SetKeys(vector<char> v){
    keySequence = v;
    for(int i=0;i<keySequence.size();++i){
        switch (keySequence[i]) {
        case 'w':
        case 'W':
            move.SetDirection(UP);
            break;

        case 's':
        case 'S':
            move.SetDirection(DOWN);
            break;
        case 'a':
        case 'A':
            move.SetDirection(LEFT);
            break;
        case 'd':
        case 'D':
            move.SetDirection(RIGHT);
            break;
        case 'r':
        case 'R':
            move.SetAttackType(SIMPLE);
            break;
        case 'q':
        case 'Q':
            move.SetAttackType(FREEZING);
            break;
        case 'e':
        case 'E':
            move.SetAttackType(WALLING);
            break;
        default:
            //can destroy balance
            move.SetAttackType(WAIT);
            break;
        }
    }
}
