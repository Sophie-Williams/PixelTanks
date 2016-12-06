#ifndef OBJECT_H
#define OBJECT_H

#include <QPoint>
#include <QPainter>

#include "helper.h"

class Object
{
protected:
    QPoint position;
public:
    Object(QPoint p = QPoint(0,0));

    virtual ~Object();

    virtual  ObjectType GetObjectType();
    QPoint GetPosition();
    virtual void Display(QPainter*);
    void SetPosition(QPoint);
  //  virtual void erase();

};

#endif // OBJECT_H
