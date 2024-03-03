#include "neural-network.h"

network_t *init_network(int input_height, int hidden_width, int hidden_height, int output_height)
{
    network_t *network;

    network = malloc(sizeof(network_t));
    if (!network)
        return (NULL);
    network->layers = malloc((hidden_width + 3) * sizeof(layer_t));
    if (!network->layers)
    {
        free(network);
        return (NULL);
    }
    network->layers[0] = init_layer(input_height, 0);
    if (!network->layers[0])
    {
        free(network->layers);
        free(network);
        return (NULL);
    }
    for (int i = 0; i < hidden_width; i++)
    {
        network->layers[i + 1] = i ? init_layer(hidden_height, hidden_height) : init_layer(hidden_height, input_height);
        if (!network->layers[i + 1])
        {
            while (--i >= 0)
                free_layer(network->layers[i]);
            free(network->layers);
            free(network);
            return(NULL);
        }
    }
    network->layers[hidden_width + 1] = init_layer(output_height, hidden_height);
    network->layers[hidden_width + 2] = NULL;
    network->input_height = input_height;
    network->hidden_width = hidden_width;
    network->hidden_height = hidden_height;
    network->output_height = output_height;
    return (network);
}

void free_network(network_t *network)
{
    if (network)
    {
        for (int i = 0; network->layers[i]; i++)
            free_layer(network->layers[i]);
        free(network->layers);
        free(network);
    }
}

double relu(double x)
{
    return (x > 0 ? x : 0);
}

double sigmoid(double x)
{
    return (1 / (1 + exp(-x)));
}

void feed_forward(network_t *network)
{
    for (int i = 0; network->layers[1]->neurons[i]; i++)
    {
        network->layers[1]->neurons[i]->value = 0.0;
        for (int j = 0; j < network->input_height; j++)
            network->layers[1]->neurons[i]->value += network->layers[0]->neurons[j]->value * network->layers[1]->neurons[i]->weights[j];
        network->layers[1]->neurons[i]->value = relu(network->layers[1]->neurons[i]->value + network->layers[1]->neurons[i]->bias); 
    }
    for (int i = 2; network->layers[i]; i++)
    {
        for (int j = 0; network->layers[i]->neurons[j]; j++)
        {
            network->layers[i]->neurons[j]->value = 0.0;
            for (int k = 0; k < network->hidden_height; k++)
                network->layers[i]->neurons[j]->value += network->layers[i - 1]->neurons[k]->value * network->layers[i]->neurons[j]->weights[k];
            network->layers[i]->neurons[j]->value = sigmoid(network->layers[i]->neurons[j]->value + network->layers[i]->neurons[j]->bias); 
        }
    }
}

// void back_propagation(network_t *network)
// {
//     for (int i = 1; network->layers[i]; i++)
//     {
//         for (int j = 0; network->layers[i]->neurons[j]; j++)
//         {
//             for (int k = 0; k < network->hidden_height; k++)
//             {
//                 network->layers[i]->neurons[j]->weights[k] = network->layers[i]->neurons[j]->
//             }
//         }
//     }
// }

void train(network_t *network, dataset_t *dataset, int iterations)
{
    double total_error;

    for (int i = 0; i < iterations; i++)
    {
        for (int j = 0; j < dataset->size; j++)
        {
            total_error = 0.0;
            for (int k = 0; network->layers[0]->neurons[k]; k++)
                network->layers[0]->neurons[k]->value = dataset->input[j][k];
            network->layers[0]->neurons[0]->value = random_double(-1, 1);
            network->layers[0]->neurons[1]->value = random_double(-1, 1);
            network->layers[0]->neurons[2]->value = random_double(-1, 1);
            feed_forward(network);
            //printf("%f\n", network->layers[0]->neurons[0]->value);
            for (int k = 0; network->layers[network->hidden_width + 1]->neurons[k]; k++)
            {
                network->layers[network->hidden_width + 1]->neurons[k]->error = pow(network->layers[network->hidden_width + 1]->neurons[k]->value - dataset->output[j][k], 2) / 2;
                total_error +=  network->layers[network->hidden_width + 1]->neurons[k]->error;
            }
            //printf("error: %f\n", total_error);
            // back_propagation(network);
        }
    }
}