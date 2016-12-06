#include "paintwidget.h"

PaintWidget::PaintWidget(
        QWidget *parent,
        int _heigth,
        int _width,
        int _bots,
        bool player) : QWidget(parent)
{
    heigth = _heigth;
    width = _width;
    world = new World(_heigth,_width,_bots,player);
    resize((_heigth+9)*cellSize,(_width+2)*cellSize);
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
    resize((_heigth+8)*cellSize,(_width+2)*cellSize);
    move(0,0);
}


void PaintWidget::AddSimpleBots(int c){
    world->AddSimpleBots(c);
}

void PaintWidget::AddNeuroBots(int c){
    world->AddNeuroBots(c);
}
