#include "neural-network.h"

layer_t *init_layer(int height, int previous_height)
{
    layer_t *layer;

    layer = malloc(sizeof(layer_t));
    if (!layer)
        return (NULL);
    layer->neurons = malloc((height + 1) * sizeof(neuron_t));
    if (!layer->neurons)
    {
        free(layer);
        return (NULL);
    }
    for (int i = 0; i < height; i++)
    {
        layer->neurons[i] = init_neuron(previous_height);
        if (!layer->neurons[i])
        {
            while (--i >= 0)
                free_neuron(layer->neurons[i]);
            free(layer->neurons);
            free(layer);
            return(NULL);
        }
    }
    layer->neurons[height] = NULL;
    return (layer);
}

void free_layer(layer_t *layer)
{
    for (int i = 0; layer->neurons[i]; i++)
        free_neuron(layer->neurons[i]);
    free(layer->neurons);
    free(layer);
}