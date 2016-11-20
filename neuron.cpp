#include "neuron.h"

#include<iostream>
using namespace std;

Neuron::Neuron()
{
    input.clear();
    output.clear();
}

Neuron::~Neuron(){
    for(int i=0;i<input.size();++i)
        delete input[i];
    input.clear();
    output.clear();
}

void Neuron::AddInputSynapse(Synapse * s){
    input.push_back(s);
}

void Neuron::AddOutputSynapse(Synapse * s){
    output.push_back(s);
}

void Neuron::SetValue(double v){
    value = v;
}

double Neuron::CalculateValue(){
    value = 0;
    for(int i=0;i<input.size();++i)
        value+=input[i]->GetValue();

   // cout<<"Neuron "<<this<<' '<<value<<'\n';
    return value;
}

void Neuron::SendValue(){
    for(int i=0;i<output.size();++i)
        output[i]->RecieveValue(value);
}
