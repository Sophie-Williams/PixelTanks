#ifndef STRATEGY_H
#define STRATEGY_H

#include "world.h"
#include "move.h"

class Tank;

class Strategy
{
protected:
    Move move;
public:
    Strategy();
    virtual ~Strategy();
    Move GetMove();
    void SetMove(Move);
    virtual Move CalculateMove(World*,Tank*) = 0;
};

#endif // STRATEGY_H
