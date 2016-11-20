#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H

#include "strategy.h"

class PlayerStrategy:public Strategy
{
    vector<char> keySequence;
    static PlayerStrategy *singleton;
    PlayerStrategy();
public:
    ~PlayerStrategy();
    static PlayerStrategy* GetInstance();
    void SetKeys(vector<char>);
    Move GetMove();
    Move CalculateMove(World *, Tank *);
};

#endif // PLAYERSTRATEGY_H
