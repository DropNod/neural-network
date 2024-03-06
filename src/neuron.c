#include "neural-network.h"

neuron_t *init_neuron(const size_t previous_height) 
{
    neuron_t *neuron;

    neuron = full_calloc(sizeof(neuron_t));
    if (!neuron)
        return (NULL);
    neuron->weights = full_calloc(previous_height * sizeof(double));
    neuron->delta_weights = full_calloc(previous_height * sizeof(double));
    if (!neuron->weights || !neuron->delta_weights )
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
        secure_free(neuron->delta_weights);
        free(neuron);
    }
}