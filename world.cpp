#include <iostream>
#include <cmath>

#include "world.h"

#include "wall.h"
#include "tank.h"
#include "playerstrategy.h"
#include "defaultstrategy.h"
#include "neuralnetwork.h"

#include <iostream>

#include <omp.h>

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
        tanks[tanks.size()-1]->SetName("Player");
    }



    //int x,y;
    Tank *t;
    QPoint p;
    neuroBotsCount = 0;
    simpleBotsCount = 0;
    for(int i=0;i<bots;++i){

        p = FindEmptyCell();
        if(rand()%4){
            t =  new Tank(p,new NeuralNetwork(neuroNetConfiguration),LEFT,neuroBotColor);
            t->SetName("Neuro Bot"+ QString(to_string(neuroBotsCount++).c_str()));
            neuroNets.push_back((NeuralNetwork*)(t->GetStrategy()));

        }
        else {
            t = new Tank(p,new DefaultStrategy(),LEFT,tankColor);
             t->SetName("SimpleBot"+ QString(to_string(simpleBotsCount++).c_str()));
        }

        map[p.x()][p.y()] = t;
        tanks.push_back(t);

    }

//walls
    for(int i=0;i<(width*heigth-bots)/4;++i){
        p = FindEmptyCell();
        map[p.x()][p.y()] = new Wall(p);

    }
}

World::~World(){
    for(int i = neuroNets.size()-1;i>=0;--i)
        neuroNets[i]->SaveConfiguration(to_string(i));

    for(int i=map.size()-1;i>=0;--i){
        for(int j=map[i].size()-1;j>=0;--j){
            if(map[i][j]!=NULL)
                delete map[i][j];
        }
    }
    map.clear();
    tanks.clear();
    for(unsigned i=0;i<bullets.size();++i)
        delete bullets[i];
    bullets.clear();
    neuroNets.clear();
    timer = 0;

}

bool comp(Tank* x,Tank* y){

    return x->GetPoints()>y->GetPoints();
}

void World::ProccesBullets(){
#pragma omp for
    for(int i=bullets.size()-1;i>=0;--i){
        Bullet *b;
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
                if(b->GetAttackType()!=WALLING && w->TakeDamage(b->GetDamage())){
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
#pragma omp for
    for(int i=tanks.size()-1;i>=0;--i){
        Tank *tank;
        QPoint p;
        tank = (Tank*)tanks[i];
        if(!tank->IsAlive()){
            if(tank->Respawn())
            {
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

                delete map[newPosition.x()][newPosition.y()];
                map[newPosition.x()][newPosition.y()] = tank;
                map[tank->GetPosition().x()][tank->GetPosition().y()] =
                        new Object(tank->GetPosition());
                tank->SetMove(Move());
                tank->SetPosition(newPosition);
            }
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

bool neuroNetsCompare(NeuralNetwork *a, NeuralNetwork *b){
    return a->GetPoints()>b->GetPoints();
}

Strategy* World::newRandomStrategy(){
    if(rand()%4)
        return newNeuroStrategy();
    return newDefaultStrategy();
}

Strategy* World::newNeuroStrategy(){
    if(rand()%3){
        int x = rand()%neuroNets.size(),
            y = rand()%neuroNets.size();
        return new NeuralNetwork((*neuroNets[x]+*neuroNets[y])/2);
    }
    return new NeuralNetwork(neuroNetConfiguration);
}

Strategy* World::newDefaultStrategy(){
    return new DefaultStrategy();
}

void World::RefreshWorld(QPainter* painter){

    ProccesTanks();
    ProccesBullets();

//#pragma omp parallel for
    for(unsigned i=0;i<map.size();++i){
       for(unsigned j=0;j<map[i].size();++j)
           map[i][j]->Display(painter);
    }
//#pragma omp parallel for
    for(int i=bullets.size()-1;i>=0;--i)
        ((Bullet*)bullets[i])->Display(painter);


    QPen pen(Qt::black);
    painter->setPen(pen);
   // stable_sort(neuroNets.begin(),neuroNets.end(),neuroNetsCompare);

    stable_sort(tanks.begin(),tanks.end(),comp);
    for(size_t i=0;i<min(10,tanks.size());++i)
        painter->drawText((worldHeight +2)*cellSize,i*cellSize+10,tanks[i]->GetInfo());


//#pragma omp parallel for
    for(int i=tanks.size()-1;i>=0;--i)
        if(tanks[i]->GetStrategy()->NeedsReset()){
            Strategy *s;
            s = tanks[i]->GetStrategy();

            vector<NeuralNetwork*>::iterator it = find(neuroNets.begin(),neuroNets.end(),s);
            if(it!=neuroNets.end())
            {
                neuroNets.erase(it);
                tanks[i]->SetStrategy(newNeuroStrategy());
                neuroNets.push_back((NeuralNetwork*)tanks[i]->GetStrategy());
                delete s;
            }
        }



    if(++timer == selectionInterval){
        timer = 0;
        Selection();
    }
}

QString World::GetLeadersTable(){
    QString a;
    for(size_t i=0;i<min(tanks.size(),10);++i)
        a += ((Tank*)tanks[i])->GetInfo()+"\n";

    return a;
}



void World::Selection(){
   // cout<<"Selection\n";

    int size = neuroNets.size();
//#pragma omp parallel for
    for(int i=size/2;i<size;++i){
        if(i%2){
            NeuralNetwork q = *neuroNets[rand()%(size/2)]+
                    *neuroNets[rand()%(size/2)];
            //delete neuroNets[i];
            *neuroNets[i]  = (q/2);}
        else
        {
           // delete neuroNets[i];
            *neuroNets[i]  = NeuralNetwork(neuroNetConfiguration);
        }
    }
    for(int i=0;i<size;++i)
        neuroNets[i]->SetPoints(0);

    std::cerr << "Selection done\n";
}

void World::AddSimpleBots(int c){
    while(c--){
        QPoint p = FindEmptyCell();
        Tank* t = new Tank(
                    p,
                    newDefaultStrategy(),
                    UP,
                    Qt::yellow,
                    defaultHealthPoints,
                    "Simple Bot"+QString(to_string(neuroBotsCount++).c_str()));
        map[p.x()][p.y()] = t;
        tanks.push_back(t);
    }
}

void World::AddNeuroBots(int c){
    while(c--){
        QPoint p = FindEmptyCell();
        NeuralNetwork *n = (NeuralNetwork*)newNeuroStrategy();

        Tank* t = new Tank(
                    p,
                    n,
                    UP,
                    neuroBotColor,
                    defaultHealthPoints,
                    "Neuro Bot "+QString(to_string(neuroBotsCount).c_str()));
        n->LoadConfiguration(to_string(neuroBotsCount++));
        map[p.x()][p.y()] = t;
        neuroNets.push_back(n);
        tanks.push_back(t);
    }
}
