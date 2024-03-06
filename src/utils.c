#include "neural-network.h"

void secure_free(void *ptr)
{
    if (ptr)
        free(ptr);
}

void *full_calloc(size_t size)
{
    return (calloc(size, size));
}

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
