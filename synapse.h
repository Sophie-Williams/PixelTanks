#ifndef SYNAPSE_H
#define SYNAPSE_H

class Synapse
{
    double value;
    double weight;

public:
    Synapse(double w = 0);
    void RecieveValue(double);
    double GetWeight();
    void SetWeight(double w);
    double GetValue();
};

#endif // SYNAPSE_H
