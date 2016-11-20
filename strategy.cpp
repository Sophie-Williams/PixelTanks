#include "strategy.h"

Strategy::Strategy(){}

Strategy::~Strategy(){}

Move Strategy::GetMove(){
    return move;
}

void Strategy::SetMove(Move m){
    move = m;
}
