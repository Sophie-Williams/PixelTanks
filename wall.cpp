#include "wall.h"

Wall::Wall(QPoint p,int h):Object(p),healthPoints(h){}

Wall::~Wall(){

}

void Wall::erase(){
    this->~Wall();
}

ObjectType Wall::GetObjectType(){
    return WALL;
}

void Wall::Display(QPainter * painter){
    QBrush brush;
    brush.setColor(wallColor);
    painter->setBrush(brush);

    QPoint p = position*cellSize;
    QPainterPath path;
    QPointF a[4]= {
        QPointF(p.x(),p.y()),
        QPointF(p.x()+cellSize,p.y()),
        QPointF(p.x()+cellSize,p.y()+cellSize),
        QPointF(p.x(),p.y()+cellSize)
    };
    path.moveTo(a[3]);
    for(int i=0;i<4;++i)
        path.lineTo(a[i]);
    painter->fillPath(path,QBrush(wallColor));
}

bool Wall::TakeDamage(int d){
    healthPoints-=d;
    return healthPoints<=0;
}
