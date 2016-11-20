#ifndef DEFAULTSTRATEGY_H
#define DEFAULTSTRATEGY_H

#include "strategy.h"

class DefaultStrategy:public Strategy
{
public:
    DefaultStrategy();
    virtual ~DefaultStrategy();
    Move GetMove();
    Move CalculateMove(World *, Tank *);
};

#endif // DEFAULTSTRATEGY_H
