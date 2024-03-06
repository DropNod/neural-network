#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define LEARNING_RATE 0.01
#define RED	"\033[31;1m"
#define END	"\033[0m"


//dataset.c
typedef struct dataset_s
{
    size_t size;
    size_t input_size;
    size_t output_size;
    double **input;
    double **output;
}   dataset_t;
dataset_t *init_dataset(const char *path);
void free_dataset(dataset_t *dataset);

//neuron.c
typedef struct neuron_s
{
    double value;
    double error;
    double *weights;
    double *delta_weights;
    double bias;
    double delta_bias;
}   neuron_t;
neuron_t *init_neuron(const size_t previous_height);
void free_neuron(neuron_t *neuron);

//layer.c
typedef struct layer_s
{
    neuron_t **neurons;
}   layer_t;
layer_t *init_layer(const size_t height, const size_t previous_height);
void free_layer(layer_t *layer);

//network.c
typedef struct network_s
{
    size_t input_height;
    size_t hidden_width;
    size_t hidden_height;
    size_t output_height;
    layer_t **layers;
}   network_t;
network_t *init_network(const size_t input_height, const size_t hidden_width, const size_t hidden_height, const size_t output_height);
void free_network(network_t *network);
int save_network(const network_t *network, const char *filename);
network_t *load_network(const char *filename);

//train.c
int train(network_t *network, const dataset_t *dataset, const size_t iterations);

//utils.c
void error(const char *error);
void secure_free(void *ptr);
void *full_calloc(const size_t size);
double random_double(const double min, const double max);
double relu(const double x);
double sigmoid(const double x);
double sigmoid_derivative(double x);