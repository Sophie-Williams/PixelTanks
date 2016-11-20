#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "strategy.h"

#include "neuron.h"

class NeuralNetwork : public Strategy
{
    int inputSize;
    int outputSize;
    vector<vector<Neuron*> > neurons;

public:
    NeuralNetwork();
    NeuralNetwork(vector<Neuron*>);
    NeuralNetwork(vector<int>);
    //NeuralNetwork(NeuralNetwork);
    virtual ~NeuralNetwork();

    vector<vector<Neuron*> > GetNeurons();

    Move CalculateMove(World*,Tank*);

    vector<double> Calculate(vector<double>);
};

#endif // NEURALNETWORK_H
