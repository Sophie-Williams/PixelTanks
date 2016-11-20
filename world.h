#ifndef WORLD_H
#define WORLD_H

#include <vector>

using std::vector;

#include "object.h"
//#include "tank.h"
//#include "bullet.h"

class World
{
protected:
    vector<vector<Object*> > map;
    vector<Object*> tanks;
    vector<Object*> bullets;
public:
    World(int heigth = worldHeight,int width = worldWidth,int bots = botsCount,bool player = false);
    ~World();
    void RefreshWorld(QPainter*);
    void ProccesBullets();
    void ProccesTanks();
    ObjectType GetObjectType(int x,int y){return map[x][y]->GetObjectType();}

    QString GetLeadersTable();
};

#endif // WORLD_H
