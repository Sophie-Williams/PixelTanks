#ifndef SYNAPSE_H
#define SYNAPSE_H

class Synapse
{
    double value;
    double weigth;

public:
    Synapse(double w = 0);
    void RecieveValue(double);
    double GetWeigth();
    void SetWeigth(double w);
    double GetValue();
};

#endif // SYNAPSE_H
