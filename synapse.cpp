#include "synapse.h"

#include <iostream>
using namespace std;

Synapse::Synapse(double w)
{
    weight = w;
    value = 0;
}

void Synapse::RecieveValue(double d){
    value = d;
}

double Synapse::GetValue(){
    return value*weight;
}

double Synapse::GetWeight(){
    return weight;
}

void Synapse::SetWeight(double w){
    weight = w;
}
