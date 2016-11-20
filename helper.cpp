#include "helper.h"

QPoint toCellCoordinats(QPoint p){
    return QPoint(p.x()/cellSize,p.y()/cellSize);
}

QPoint toSimpleCoordinats(QPoint p){
    return QPoint((2*p.x()+1)*cellSize/2,(2*p.y()+1)*cellSize/2);
}

QPoint moveVector(Direction d){
    switch (d) {
    case UP:
        return QPoint(-1,0);
        break;
    case RIGHT:
        return QPoint(0,1);
        break;
    case DOWN:
        return QPoint(1,0);
        break;
    case LEFT:
        return QPoint(0,-1);
    default:
        return QPoint(0,0);
        break;
    }
}
