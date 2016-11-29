#include "neuralnetwork.h"

#include "tank.h"
#include "world.h"

#include<set>
using std::set;
#include<deque>
using std::deque;
#include<iostream>
using std::cout;

#include <map>
using std::map;

NeuralNetwork::NeuralNetwork()
{

}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& a){
    inputSize = a.inputSize;
    outputSize = a.outputSize;
    neurons = vector< Neuron*> (a.neurons.size());
    int to;
    Synapse *s;
    map<Synapse*,int> unused;
    unused.clear();
    vector<Synapse*> in,out;
    int pos;
    for(int i=0;i<a.neurons.size();++i)
    {
        in = a.neurons[i]->GetInput();
        out = a.neurons[i]->GetOutput();

        neurons[i] = new Neuron();
        for(int j = in.size()-1;j>=0;--j)
        {
            pos = unused[in[j]];
            //cout<<pos<<' ';
            unused.erase(in[j]);
            s = new Synapse(in[j]->GetWeigth());
            //s = new Synapse(rand()%21-10);
            neurons[pos]->AddOutputSynapse(s);
            neurons[i]->AddInputSynapse(s);
        }

        for(int j=out.size()-1;j>=0;--j)
            unused[out[j]] = i;
    }
}

NeuralNetwork::~NeuralNetwork(){
    vector<Synapse*> in;
    for(int i=neurons.size()-1;i>=0;--i){
       /* in = neurons[i]->GetInput();
        for(int i=in.size()-1;i>=0;--i)
            delete in[i];*/
        delete neurons[i];
    }
    neurons.clear();
}

NeuralNetwork::NeuralNetwork(vector<int> sizes){
    if(sizes.size()<2)
        return;
    inputSize = sizes[0];
    outputSize = sizes[sizes.size()-1];

    int sum = 0;
    for(int i=0;i<sizes.size();++i)
        sum+=sizes[i];

    neurons = vector<Neuron*>  (sum);

    int position = 0;

    for(int i=0;i<inputSize;++i)
        neurons[position++] = new Neuron();

    Synapse *s;
    int previousBegin = 0;
    int curentBegin = position;
    for(unsigned i=1;i<sizes.size();++i){
        for(int j=0;j<sizes[i];++j){
            neurons[position] = new Neuron();
            for(int g=previousBegin;g<curentBegin;++g){
                s = new Synapse(1.*(rand()%21 - 10));
                neurons[g]->AddOutputSynapse(s);
                neurons[position]->AddInputSynapse(s);
            }
            ++position;
        }
        previousBegin = curentBegin;
        curentBegin = position;
    }
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
        input.push_back(2*(world->GetObjectType(x,y) == TANK) - 1);
        input.push_back(1./sqrt(1.*abs(tx-x+ty-y)));
    }
    vector<double> output = Calculate(input);

/*
    cout<<this<<'\n';
    for(unsigned i=0;i<input.size();++i)cout<<(int)input[i]<<' ';cout<<'\n';
    for(unsigned i=0;i<output.size();++i)cout<<(int)output[i]<<' ';cout<<'\n';
*/
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


    //if(a.GetAttack()!=WAIT)++points;

    return a;
}

vector<Neuron*>  NeuralNetwork::GetNeurons(){
    return neurons;
}

vector<double> NeuralNetwork::Calculate(vector<double> input){

    if(input.size()!=inputSize)
        return vector<double>();

    int i=0;

    for(;i<inputSize;++i){
        neurons[i]->SetValue(input[i]);
        neurons[i]->SendValue();
    }

    int end = neurons.size()-1;

    for(;i<end-outputSize;++i){
            neurons[i]->CalculateValue();
            neurons[i]->SendValue();}

    vector<double> res;

    for(;i<end;++i)
        res.push_back(neurons[i]->CalculateValue());

    return res;
}

NeuralNetwork NeuralNetwork::operator=(const NeuralNetwork& a){
    inputSize = a.inputSize;
    outputSize = a.outputSize;
    neurons = vector< Neuron*> (a.neurons.size());
    int to;
    Synapse *s;
    map<Synapse*,int> unused;
    unused.clear();
    vector<Synapse*> in,out;
    int pos;
    for(int i=0;i<a.neurons.size();++i)
    {
        in = a.neurons[i]->GetInput();
        out = a.neurons[i]->GetOutput();

        neurons[i] = new Neuron();
        for(int j = in.size()-1;j>=0;--j)
        {
            pos = unused[in[j]];
            //cout<<pos<<' ';
            unused.erase(in[j]);
            s = new Synapse();
            neurons[pos]->AddOutputSynapse(s);
            neurons[i]->AddInputSynapse(s);
        }

        for(int j=out.size()-1;j>=0;--j)
            unused[out[j]] = i;
    }
    return *this;
}

NeuralNetwork operator*(const NeuralNetwork& b,double w){
    NeuralNetwork a = b;
    vector<Synapse*> in;
    for(int i=a.neurons.size()-1;i>=0;--i){
        in = a.neurons[i]->GetInput();
        for(int j=in.size()-1;j>=0;--j)
            in[j]->SetWeigth(in[j]->GetWeigth()*w);
    }
    return a;
}

NeuralNetwork operator/(const NeuralNetwork& b,double w){
    NeuralNetwork a = b;
    if(w==0)
        return a;
    return a*(1./w);
}

NeuralNetwork operator+(const NeuralNetwork& a, const NeuralNetwork& b){
    NeuralNetwork c = b;
    if(a.neurons.size()!=b.neurons.size())
        return c;

    vector<Synapse*> in1,in2,in3;
    for(int i=a.neurons.size()-1;i>=0;--i){
        in1 = a.neurons[i]->GetInput();
        in2 = b.neurons[i]->GetInput();
        in3 = c.neurons[i]->GetInput();
        if(in1.size()!=in2.size())
            return b;
        for(int j=in1.size()-1;j>=0;--j)
            in3[j]->SetWeigth(in1[j]->GetWeigth()+in2[j]->GetWeigth());
    }
    return c;
}
