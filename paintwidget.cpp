#include "paintwidget.h"

PaintWidget::PaintWidget(
        QWidget *parent,
        int _heigth,
        int _width,
        int _bots,
        bool player) : QWidget(parent)
{
    world = new World(_heigth,_width,_bots,player);
    resize((_heigth+2)*cellSize,(_width+2)*cellSize);
    move(0,0);

}

PaintWidget::~PaintWidget(){
    delete world;
}

void PaintWidget::paintEvent(QPaintEvent *event){
    QPainter *painter = new QPainter(this);
    world->RefreshWorld(painter);
    delete painter;
}

void PaintWidget::ActivateWindow(){
    activateWindow();
}

void PaintWidget::InitMap(int _heigth,int _width,int _bots,bool player){
    if(world!=NULL)
        delete world;
    world = new World(_heigth,_width,_bots,player);
    resize((_heigth+2)*cellSize,(_width+2)*cellSize);
    move(0,0);
}
