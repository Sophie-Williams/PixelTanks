#include <iostream>
#include <cmath>

#include "world.h"

#include "wall.h"
#include "tank.h"
#include "playerstrategy.h"
#include "defaultstrategy.h"
#include "neuralnetwork.h"

#include <iostream>
using namespace std;

#define min(a,b) (a<b?(a):(b))

QPoint World::FindEmptyCell(){
    int heigth = map.size()-2;
    int width = map[0].size()-2;
    int x,y;
    do{
        x = rand()%heigth+1;
        y = rand()%width+1;
    }
    while(map[x][y]->GetObjectType()!=OBJECT);
    delete map[x][y];
    return QPoint(x,y);
}

World::World(int heigth,int width,int bots,bool player)
{
    timer = 0;
    map = vector<vector<Object*> > (heigth+2,vector<Object*> (width+2,NULL));

    for(int i=0;i<width+2;++i)
        map[0][i] = new Wall(QPoint(0,i),maxHealth);

    for(int i=0;i<width+2;++i)
        map[heigth+1][i] = new Wall(QPoint(heigth+1,i),maxHealth);

    for(int i=0;i<heigth+2;++i)
        map[i][0] = new Wall(QPoint(i,0),maxHealth);

    for(int i=0;i<heigth+2;++i)
        map[i][width+1] = new Wall(QPoint(i,width+1),maxHealth);





    for(int i=1;i<=heigth;++i)
        for(int j=1;j<=width;++j)
                map[i][j] = new Object(QPoint(i,j));

    if(player){
        delete map[1][1];
        map[1][1] = new Tank(QPoint(1,1),PlayerStrategy::GetInstance(),UP,playerColor);
        tanks.push_back((Tank*)map[1][1]);
    }



    int x,y;
    Tank *t;
    QPoint p;
    for(int i=0;i<bots;++i){

        p = FindEmptyCell();
        if(rand()%4){
        t =  new Tank(p,new NeuralNetwork(neuroNetConfiguration),LEFT,neuroBotColor);
        neuroNets.push_back((NeuralNetwork*)(t->GetStrategy()));
        }
        else t = new Tank(p,new DefaultStrategy(),LEFT,tankColor);
        map[p.x()][p.y()] = t;
        tanks.push_back(t);
    }


    for(int i=0;i<(width*heigth-bots)/4;++i){
        p = FindEmptyCell();
        map[p.x()][p.y()] = new Wall(p);

    }
}

World::~World(){
    for(int i=map.size()-1;i>=0;--i){
        for(int j=map[i].size()-1;j>=0;--j){
            if(map[i][j]!=NULL)
                delete map[i][j];
        }
    }
    map.clear();
    tanks.clear();
    for(int i=0;i<bullets.size();++i)
        delete bullets[i];
    bullets.clear();
    neuroNets.clear();
    timer = 0;
}

bool comp(Object* a,Object* b){
    Tank *x,*y;
    x = (Tank*)a;
    y = (Tank*)b;
    return x->GetPoints()>y->GetPoints();
}

void World::ProccesBullets(){

    Bullet *b;
    for(int i=bullets.size()-1;i>=0;--i){
        b = (Bullet*)bullets[i];
        bool f = b->Shift();
        QPoint pos =
            toCellCoordinats(b->GetPosition());

        switch (map[pos.x()][pos.y()]->GetObjectType()) {
            case TANK:{
                Tank* t = (Tank*)map[pos.x()][pos.y()];
                if(b->GetOwner() == t)
                    break;

                t->TakeDamage(b->GetDamage());
                t->SetDelay(b->GetFreeze());
                if(b->GetAttackType() == FREEZING)
                    t->SetColor(frozenColor);
                b->GetOwner()->AddPoints(b->GetDamage());
                if(!t->IsAlive()){
                    b->GetOwner()->AddPoints(killPoints);
                    map[pos.x()][pos.y()] =
                            new Object(QPoint(pos.x(),pos.y()));
                }

                bullets.erase(bullets.begin()+i);
                delete b;
                continue;
                break;}
            case WALL:{
                Wall *w = (Wall*)map[pos.x()][pos.y()];
                if(w->TakeDamage(b->GetDamage())){
                    delete w;
                    map[pos.x()][pos.y()] = new Object(pos);
                }
                bullets.erase(bullets.begin()+i);
                delete b;
                continue;
                break;}
            case OBJECT:
                break;
            }

        if(!f){
            if(b->GetAttackType()==WALLING && map[pos.x()][pos.y()]->GetObjectType() == OBJECT){
                delete map[pos.x()][pos.y()];
                map[pos.x()][pos.y()] = new Wall(pos,wallHealthPoints);
            }

            bullets.erase(bullets.begin()+i);
            delete b;
        }
    }

}

void World::ProccesTanks(){
    Tank *tank;
    QPoint p;
    for(int i=tanks.size()-1;i>=0;--i){
        tank = (Tank*)tanks[i];
        if(!tank->IsAlive()){
            if(tank->Respawn())
            {
                int x,y;
                p = FindEmptyCell();
                tank->SetPosition(p);
                map[p.x()][p.y()] = tank;
            }
            else continue;
        }
        Move move = tank->GetMove(this);
        QPoint newPosition = tank->GetPosition();
        if(tank->GetDirection() == move.GetDirection() || move.GetDirection() == NONE){
            switch (move.GetDirection()) {
            case RIGHT:
                newPosition.setX(newPosition.x()+1);
                break;
            case LEFT:
                newPosition.setX(newPosition.x()-1);
                break;
            case DOWN:
                newPosition.setY(newPosition.y()+1);
                break;
            case UP:
                newPosition.setY(newPosition.y()-1);
                break;
            default:
                break;
            }
            if(map[newPosition.x()][newPosition.y()]->GetObjectType() == OBJECT){
                tank->AddPoints(100);
                delete map[newPosition.x()][newPosition.y()];
                map[newPosition.x()][newPosition.y()] = tank;
                map[tank->GetPosition().x()][tank->GetPosition().y()] =
                        new Object(tank->GetPosition());
                tank->SetMove(Move());
                tank->SetPosition(newPosition);
            }
       //     tank->SetMove(Move());
        }
        else {
            tank->SetDirection(move.GetDirection());
            tank->SetMove(Move());
            tank->SetDelay(turnDelay);
        }

        if(move.GetAttack() !=WAIT){
            Attack attack;
            switch  (move.GetAttack()) {
            case SIMPLE:
                attack = simpleAttack;
                break;
            case FREEZING:
                attack = freezeAttack;
                break;
            case WALLING:
                attack = wallAttck;
                break;
            case WAIT:
                //to hide compiler warning
                break;
            }
            bullets.push_back(new Bullet(tank,attack,toSimpleCoordinats(tank->GetPosition()),tank->GetDirection()));
        }
    }
}


void World::RefreshWorld(QPainter* painter){

    ProccesTanks();
    ProccesBullets();

    for(unsigned i=0;i<map.size();++i){
       for(unsigned j=0;j<map[i].size();++j)
           map[i][j]->Display(painter);
    }
    for(int i=bullets.size()-1;i>=0;--i)
        ((Bullet*)bullets[i])->Display(painter);

    stable_sort(tanks.begin(),tanks.end(),comp);
    QPen pen(Qt::black);
    painter->setPen(pen);
    ++timer;
    if(timer == selectionInterval){
        timer = 0;
        Selection();
    }
}

QString World::GetLeadersTable(){
    QString a;
    for(int i=0;i<min(tanks.size(),10);++i)
        a += ((Tank*)tanks[i])->GetInfo()+"\n";

    return a;

}

bool neuroNetsCompare(NeuralNetwork *a, NeuralNetwork *b){
    return a->GetPoints()>b->GetPoints();
}

void World::Selection(){
   // cout<<"Selection\n";
    sort(neuroNets.begin(),neuroNets.end(),neuroNetsCompare);
    int size = neuroNets.size();
    for(int i=size/2;i<size;++i){
        if(i%2){
            NeuralNetwork q = *neuroNets[rand()%(size/2)]+
                    *neuroNets[rand()%(size/2)];

        *neuroNets[i]  = q/2;}
        else
        {
            delete neuroNets[i];
            neuroNets[i]  = new NeuralNetwork(neuroNetConfiguration);
        }
    }
    for(int i=0;i<size;++i)
        neuroNets[i]->SetPoints(0);
}
