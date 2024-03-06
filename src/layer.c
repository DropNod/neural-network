#include "neural-network.h"

layer_t *init_layer(const size_t height, const size_t previous_height)
{
    layer_t *layer;

    layer = full_calloc(sizeof(layer_t));
    if (!layer)
        return (NULL);
    layer->neurons = full_calloc((height + 1) * sizeof(neuron_t));
    if (!layer->neurons)
        return (free(layer), NULL);
    for (size_t i = 0; i < height; i++)
    {
        layer->neurons[i] = init_neuron(previous_height);
        if (!layer->neurons[i])
            return (free_layer(layer), NULL);
    }
    return (layer);
}

void free_layer(layer_t *layer)
{
    if (layer)
    {
        for (int i = 0; layer->neurons[i]; i++)
            free_neuron(layer->neurons[i]);
        secure_free(layer->neurons);
        free(layer);
    }
}