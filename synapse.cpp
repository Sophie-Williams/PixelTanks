#include "synapse.h"

#include <iostream>
using namespace std;

Synapse::Synapse(double w)
{
    weight = w;
    value = 0;
}

void Synapse::RecieveValue(double d){
  //  cout<<"Recieved "<<this<<' '<<d<<'\n';
    value = d;
}

double Synapse::GetValue(){
  //  cout<<"Sended "<<this<<' '<<value*weight<<'\n';

    return value*weight;
}

double Synapse::GetWeight(){
    return weight;
}

void Synapse::SetWeight(double w){
    weight = w;
}
