#include "neural-network.h"

static void feed_forward(network_t *network)
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

    if (network->input_height != dataset->input_size || network->output_height != dataset->output_size )
        return ;
    for (int i = 0; i < iterations; i++)
    {
        for (int j = 0; j < dataset->size; j++)
        {
            total_error = 0.0;
            for (int k = 0; network->layers[0]->neurons[k]; k++)
                network->layers[0]->neurons[k]->value = dataset->input[j][k];
            feed_forward(network);
            for (int k = 0; network->layers[network->hidden_width + 1]->neurons[k]; k++)
            {
                network->layers[network->hidden_width + 1]->neurons[k]->error = pow(network->layers[network->hidden_width + 1]->neurons[k]->value - dataset->output[j][k], 2) / 2;
                total_error +=  network->layers[network->hidden_width + 1]->neurons[k]->error;
            }
            printf("error: %f\n", total_error);
            // back_propagation(network);
        }
    }
}