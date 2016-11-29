#include "synapse.h"

#include <iostream>
using namespace std;

Synapse::Synapse(double w)
{
    weigth = w;
    value = 0;
}

void Synapse::RecieveValue(double d){
    value = d;
}

double Synapse::GetValue(){
    return value*weigth;
}

double Synapse::GetWeigth(){
    return weigth;
}

void Synapse::SetWeigth(double w){
    weigth = w;
}
