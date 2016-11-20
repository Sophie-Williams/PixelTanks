#ifndef NEURON_H
#define NEURON_H

#include <synapse.h>

#include <vector>
using std::vector;

class Neuron
{
    vector<Synapse*> input;
    vector<Synapse*> output;

    double value;

public:
    Neuron();
    ~Neuron();
    double CalculateValue();
    void SendValue();
    void SetValue(double);

    void AddInputSynapse(Synapse*);
    void AddOutputSynapse(Synapse*);

    void RemoveInputSynapse(Synapse*);
    void RemoveOutputSynapse(Synapse*);
};

#endif // NEURON_H
