#ifndef STRATEGY_H
#define STRATEGY_H

//#include "world.h"
#include "move.h"

class Tank;
class World;

class Strategy
{
protected:
    Move move;
    int points;
    int fuel;
    int deathFuel;
    int damageFuel;
    int moveFuel;
    int shotFuel;
    int waitFuel;
public:
    Strategy();
    virtual ~Strategy();
    Move GetMove();
    void SetMove(Move);
    virtual Move CalculateMove(World*,Tank*) = 0;
    void AddPoints(int p){points+=p;fuel+=damageFuel*p;}
    void SetPoints(int p){points=p;}
    int GetPoints(){return points;}
    bool NeedsReset();
    int GetFuel(){return fuel;}
};

#endif // STRATEGY_H
