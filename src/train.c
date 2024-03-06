#include "neural-network.h"

static void feed_forward(network_t *network)
{
    for (size_t i = 0; network->layers[1]->neurons[i]; i++)
    {
        network->layers[1]->neurons[i]->value = 0.0;
        for (size_t j = 0; j < network->input_height; j++)
            network->layers[1]->neurons[i]->value += network->layers[0]->neurons[j]->value * network->layers[1]->neurons[i]->weights[j];
        network->layers[1]->neurons[i]->value = relu(network->layers[1]->neurons[i]->value + network->layers[1]->neurons[i]->bias); 
    }
    for (size_t i = 2; network->layers[i]; i++)
    {
        for (size_t j = 0; network->layers[i]->neurons[j]; j++)
        {
            network->layers[i]->neurons[j]->value = 0.0;
            for (size_t k = 0; k < network->hidden_height; k++)
                network->layers[i]->neurons[j]->value += network->layers[i - 1]->neurons[k]->value * network->layers[i]->neurons[j]->weights[k];
            network->layers[i]->neurons[j]->value = sigmoid(network->layers[i]->neurons[j]->value + network->layers[i]->neurons[j]->bias); 
        }
    }
}

static void back_propagate(network_t *network, double *expected_output)
{
    double output;
    double error;
    size_t previous_layer_height;
    neuron_t *tmp;

    for (size_t i = 0; network->layers[network->hidden_width + 1]->neurons[i]; i++)
    {
        tmp = network->layers[network->hidden_width + 1]->neurons[i];
        output = tmp->value;
        error = (expected_output[i] - output) * sigmoid_derivative(output);
        for (size_t j = 0; j < network->hidden_height; j++)
        {
            tmp->delta_weights[j] = LEARNING_RATE * error * network->layers[network->hidden_width]->neurons[j]->value;
            tmp->weights[j] += tmp->delta_weights[j];
        }
        tmp->delta_bias = LEARNING_RATE * error;
        tmp->bias += tmp->delta_bias;
    }
    for (size_t i = network->hidden_width; i > 0; i--)
    {
        if (i == 1)
            previous_layer_height = network->input_height;
        else
            previous_layer_height = network->hidden_height;
        for (size_t j = 0; network->layers[i]->neurons[j]; j++)
        {
            tmp = network->layers[i]->neurons[j];
            error = 0.0;
            for (size_t k = 0; network->layers[i + 1]->neurons[k]; k++)
                error += network->layers[i + 1]->neurons[k]->delta_weights[j] * network->layers[i + 1]->neurons[k]->weights[j];
            error *= sigmoid_derivative(tmp->value);
            for (size_t k = 0; k < previous_layer_height; k++)
            {
                tmp->delta_weights[k] = LEARNING_RATE * error * network->layers[i - 1]->neurons[k]->value;
                tmp->weights[k] += tmp->delta_weights[k];
            }
            tmp->delta_bias = LEARNING_RATE * error;
            tmp->bias += tmp->delta_bias;
            //printf("error: %lf\n",  tmp->delta_bias);
        }
    }
}

int train(network_t *network, const dataset_t *dataset, const size_t iterations)
{
    double total_error;

    if (network->input_height != dataset->input_size || network->output_height != dataset->output_size )
        return (0);
    for (int i = 0; i < iterations; i++)
    {
        for (int j = 0; j < dataset->size; j++)
        {
            total_error = 0.0;
            for (int k = 0; k < network->input_height; k++)
                network->layers[0]->neurons[k]->value = dataset->input[j][k];
            feed_forward(network);
            for (int k = 0; k < network->output_height; k++)
            {
                network->layers[network->hidden_width + 1]->neurons[k]->error = pow(network->layers[network->hidden_width + 1]->neurons[k]->value - dataset->output[j][k], 2) / 2;
                total_error +=  network->layers[network->hidden_width + 1]->neurons[k]->error;
            }
            printf("error: %lf\n", total_error);
            back_propagate(network, dataset->output[j]);
        }
    }
    return (1);
}