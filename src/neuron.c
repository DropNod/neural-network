#include "neural-network.h"

neuron_t *init_neuron(int previous_height) 
{
    neuron_t *neuron;

    neuron = malloc(sizeof(neuron_t));
    if (!neuron)
        return (NULL);
    neuron->value = 0.0;
    neuron->error = 0.0;
    neuron->weights = malloc(previous_height * sizeof(double));
    if (!neuron->weights)
    {
        free(neuron);
        return (NULL);
    }
    for (int i = 0; i < previous_height; i++)
        neuron->weights[i] = random_double(-0.1, 0.1);
    neuron->bias = random_double(-0.1, 0.1);
    return (neuron);
}

void free_neuron(neuron_t *neuron)
{
    free(neuron->weights);
    free(neuron);
}