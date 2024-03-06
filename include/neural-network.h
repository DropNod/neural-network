#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "cJSON.h"

#define LEARNING_RATE 1

//dataset.c
typedef struct dataset_s
{
    double **input;
    double **output;
    size_t size;
}   dataset_t;
dataset_t *init_dataset(char *path);
void free_dataset(dataset_t *dataset);

//neuron.c
typedef struct neuron_s
{
    double value;
    double error;
    double *weights;
    double bias;
}   neuron_t;
neuron_t *init_neuron(int previous_height);
void free_neuron(neuron_t *neuron);

//layer.c
typedef struct layer_s
{
    neuron_t **neurons;
}   layer_t;
layer_t *init_layer(int height, int previous_height);
void free_layer(layer_t *layer);

//network.c
typedef struct network_s
{
    int input_height;
    int hidden_width;
    int hidden_height;
    int output_height;
    layer_t **layers;
}   network_t;
network_t *init_network(int input_height, int hidden_width, int hidden_height, int output_height);
void free_network(network_t *network);
int save_network(network_t *network, char *filename);
network_t *load_network(char *filename);

//train.c
void train(network_t *network, dataset_t *dataset, int iterations);

//utils.c
double random_double(double min, double max);
double relu(double x);
double sigmoid(double x);