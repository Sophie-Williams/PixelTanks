#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "strategy.h"

#include "neuron.h"

#include <string>
using std::string;

class NeuralNetwork : public Strategy
{
    int inputSize;
    int outputSize;
    vector<Neuron*> neurons;

public:
    NeuralNetwork();
    NeuralNetwork(const NeuralNetwork&);
    NeuralNetwork(vector<Neuron*>);
    NeuralNetwork(vector<int>);
    //NeuralNetwork(NeuralNetwork);
    virtual ~NeuralNetwork();

    vector<Neuron*>  GetNeurons();

    Move CalculateMove(World*,Tank*);

    vector<double> Calculate(vector<double>);
    NeuralNetwork operator=(const NeuralNetwork&);
    friend NeuralNetwork operator*(const NeuralNetwork&,double);
    friend NeuralNetwork operator/(const NeuralNetwork&,double);
    friend NeuralNetwork operator+(const NeuralNetwork&,const NeuralNetwork&);
    void LoadConfiguration(string filename);
    void SaveConfiguration(string filename);
};




#endif // NEURALNETWORK_H
