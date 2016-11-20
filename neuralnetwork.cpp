#include "neuralnetwork.h"

#include "tank.h"
#include "world.h"

#include<set>
using std::set;
#include<deque>
using std::deque;
#include<iostream>
using std::cout;

NeuralNetwork::NeuralNetwork()
{

}

NeuralNetwork::~NeuralNetwork(){

}

NeuralNetwork::NeuralNetwork(vector<int> sizes){
    if(sizes.size()<2)
        return;
    inputSize = sizes[0];
    outputSize = sizes[sizes.size()-1];

    neurons = vector<vector<Neuron*> > (sizes.size(),vector<Neuron*>());
    for(int i=0;i<inputSize;++i)
        neurons[0].push_back(new Neuron());

    Synapse *s;
    for(unsigned i=1;i<sizes.size();++i)
        for(int j=0;j<sizes[i];++j){
            neurons[i].push_back(new Neuron());
            for(unsigned g=0;g<neurons[i-1].size();++g){
                s = new Synapse(1.*(rand()%10));
                neurons[i-1][g]->AddOutputSynapse(s);
                neurons[i][j]->AddInputSynapse(s);}}



}

Move NeuralNetwork::CalculateMove(World* world, Tank* tank){
    vector<double> input;
    int x,y,tx,ty;
    tx = tank->GetPosition().x();
    ty = tank->GetPosition().y();
    vector<int> dx(4),dy(4);

    switch (tank->GetDirection()) {
    case UP:
        dx = {-1,0,0,1};
        dy = {0,1,-1,0};
        break;
    case DOWN:
        dx = {1,0,0,-1};
        dy = {0,1,-1,0};
        break;
    case LEFT:
        dy = {-1,0,0,1};
        dx = {0,1,-1,0};
        break;
    case RIGHT:
        dy = {1,0,0,-1};
        dx = {0,1,-1,0};
        break;
    default:
        break;
    }

    for(int i=0;i<4;++i){
        x = tx+dx[i];y = ty+dy[i];
        while(world->GetObjectType(x,y) == OBJECT){
            x+=dx[i];
            y+=dy[i];
        }
        input.push_back(world->GetObjectType(x,y) == TANK);
        input.push_back(1./sqrt(1.*abs(tx-x+ty-y)));
    }
    vector<double> output = Calculate(input);


    cout<<this<<'\n';
    for(int i=0;i<input.size();++i)cout<<(int)input[i]<<' ';cout<<'\n';
    for(int i=0;i<output.size();++i)cout<<(int)output[i]<<' ';cout<<'\n';

    Move a;
    int mPos = 0;
    for(int i=1;i<5;++i)
        if(output[i]>output[mPos])
            mPos = i;

    a.SetDirection(Direction(mPos));


    mPos = 5;
    for(int i=5;i<=8;++i)
        if(output[i]>output[mPos])
            mPos = i;

    a.SetAttackType((AttackType)(mPos-5));


    return a;
}

vector<vector<Neuron*> > NeuralNetwork::GetNeurons(){
    return neurons;
}

vector<double> NeuralNetwork::Calculate(vector<double> input){
    for(int i = input.size()-1;i>=0;--i){
        neurons[0][i]->SetValue(input[i]);
        neurons[0][i]->SendValue();
    }

    int end = neurons.size()-1;

    for(int i=1;i<end;++i)
        for(unsigned j=0;j<neurons[i].size();++j){
            neurons[i][j]->CalculateValue();
            neurons[i][j]->SendValue();}

    vector<double> res;

    for(int i=neurons[end].size()-1;i>=0;--i)
        res.push_back(neurons[end][i]->CalculateValue());

    return res;
}
