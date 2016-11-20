#ifndef WALL_H
#define WALL_H

#include "object.h"
#include "bullet.h"

class Wall : public Object
{
    int healthPoints;
public:
    Wall(QPoint p = QPoint(0,0),int h = 100);
    virtual ~Wall();
    ObjectType GetObjectType();
    void Display(QPainter*);
    void erase();
    bool TakeDamage(int);
};

#endif // WALL_H
