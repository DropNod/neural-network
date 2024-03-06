#include "neural-network.h"

double random_double(double min, double max)
{
    return (min + ((double)rand() / RAND_MAX) * (max - min));
}

double relu(double x)
{
    return (x > 0 ? x : 0);
}

double sigmoid(double x)
{
    return (1 / (1 + exp(-x)));
}
