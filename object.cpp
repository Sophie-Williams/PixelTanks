#include "object.h"

Object::Object(QPoint p):position(p){}


Object::~Object(){}


QPoint Object::GetPosition(){
    return position;
}

ObjectType Object::GetObjectType(){
    return OBJECT;
}

void Object::Display(QPainter* painter){
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
    painter->fillPath(path,QBrush(backgroundColor));
}


void Object::SetPosition(QPoint p){
    position = p;
}
