#include "neural-network.h"

neuron_t *init_neuron(const size_t previous_height) 
{
    neuron_t *neuron;

    neuron = full_calloc(sizeof(neuron_t));
    if (!neuron)
        return (NULL);
    neuron->value = 0.0;
    neuron->error = 0.0;
    neuron->weights = full_calloc(previous_height * sizeof(double));
    if (!neuron->weights)
        return (free(neuron), NULL);
    for (size_t i = 0; i < previous_height; i++)
        neuron->weights[i] = random_double(-0.1, 0.1);
    neuron->bias = random_double(-0.1, 0.1);
    return (neuron);
}

void free_neuron(neuron_t *neuron)
{
    if (neuron)
    {
        secure_free(neuron->weights);
        free(neuron);
    }
}