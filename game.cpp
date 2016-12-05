#include "game.h"
#include "ui_game.h"

#include <QPainter>
#include <QKeyEvent>

#include <vector>
using std::vector;
using std::swap;

#include <QTableView>
#include <QTableWidget>

#include <iostream>
using std::cout;

#include "helper.h"

#include "tank.h"

Game::Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    //world = new World(worldHeight,worldWidth);
   // ui->SettingsBox->hide();
    widget = new PaintWidget(this);
    widget->show();

    ui->HeigthBox->setMinimum(15);
    ui->HeigthBox->setMaximum(40);
    ui->WidthBox->setMinimum(15);
    ui->WidthBox->setMaximum(30);

    ui->SimpleBotsCount->setMinimum(1);
    ui->SimpleBotsCount->setMaximum(14);

    ui->NeuroBotsCount->setMinimum(1);
    ui->NeuroBotsCount->setMaximum(14);


    ui->HeigthBox->setValue(40);
    ui->WidthBox->setValue(30);

}

Game::~Game()
{
    delete ui;
}

void Game::paintEvent(QPaintEvent *event){
   //if(event->isAccepted()){;}
    PlayerStrategy::GetInstance()->SetKeys(keys);

}

void Game::keyPressEvent(QKeyEvent* event){
    std::string s;
    s = event->text().toStdString();
    if(s.size()<=0)
        return;

    keys.push_back(s[0]);

    //experimental, may cause problems
    //refreshWorld();
}


void Game::initTimer(){
    QTimer *timer = NULL;
    if(timer == NULL){
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(refreshWorld()));
    }
    timer->start(renewInterval);
}

void Game::refreshWorld(){
    std::cerr << "ref\n";
  PlayerStrategy::GetInstance()->SetKeys(keys);
  keys.clear();
  update();
  widget->update();

}

void Game::on_StartGame_clicked()
{
    widget->InitMap(
                ui->HeigthBox->value(),
                ui->WidthBox->value(),
                5,
                ui->EnablePlayer->isChecked()
                );

    if(ui->EnablePlayer->isChecked()){
        widget->activateWindow();
        //ui->SettingsBox->hide();
    }


}

void Game::on_WidthBox_valueChanged(int a)
{
    ui->SimpleBotsCount->setMaximum(a*ui->HeigthBox->value()/16);
    ui->NeuroBotsCount->setMaximum(a*ui->HeigthBox->value()/16);
}

void Game::on_HeigthBox_valueChanged(int a)
{
    ui->SimpleBotsCount->setMaximum(a*ui->WidthBox->value()/16);
    ui->NeuroBotsCount->setMaximum(a*ui->WidthBox->value()/16);
}

void Game::on_AddNeuroBots_clicked()
{
    widget->AddNeuroBots(ui->NeuroBotsCount->value());
}

void Game::on_AddSimpleBots_clicked()
{
    widget->AddSimpleBots(ui->SimpleBotsCount->value());
}
