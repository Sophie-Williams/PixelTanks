#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

#include "world.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
    int heigth;
    int width;
    World * world;
public:
    explicit PaintWidget(QWidget *parent = 0,int _height = worldHeight,int _width = worldWidth,int _bots = botsCount,bool player = false);
    void ActivateWindow();
    void InitMap(int height,int width,int bots,bool player);
    ~PaintWidget();

    void AddSimpleBots(int);
    void AddNeuroBots(int);

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
signals:

public slots:
};

#endif // PAINTWIDGET_H
