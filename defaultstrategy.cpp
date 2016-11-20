#include "defaultstrategy.h"

DefaultStrategy::DefaultStrategy(){}

DefaultStrategy::~DefaultStrategy(){}

Move DefaultStrategy::GetMove(){
    return move = Move(QPoint(0,0),AttackType(rand()%4),Direction(rand()%5));
}

Move DefaultStrategy::CalculateMove(World *, Tank *){
    return move = Move(QPoint(0,0),AttackType(rand()%4),Direction(rand()%5));
}
