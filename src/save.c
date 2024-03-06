#include "neural-network.h"

int save_network(network_t *network, char *filename)
{
    FILE *file;
    int previous_layer_height;

    if (!network)
        return (0);
    file = fopen(filename, "w");
    if (!file)
        return (0);
    fprintf(file, "network:\n{\n\tinput_height: %d\n\thidden_width: %d\n\thidden_height: %d\n\toutput_height: %d\n\tlayers:\n",
        network->input_height,
        network->hidden_width,
        network->hidden_height,
        network->output_height);
    for (int i = 0; network->layers[i]; i++)
    {
        if (i == 0)
            previous_layer_height = 0;
        else if (i == 1)
            previous_layer_height = network->input_height;
        else
            previous_layer_height = network->hidden_height;
        fprintf(file, "\t{\n\t\tneurons:\n");
        for (int j = 0; network->layers[i]->neurons[j]; j++)
        {
            fprintf(file, "\t\t{\n\t\t\tvalue: %lf\n\t\t\tweights: [", network->layers[i]->neurons[j]->value);
            for (int k = 0; k < previous_layer_height; k++)
                fprintf(file, k + 1 < previous_layer_height ? "%lf, " : "%lf", network->layers[i]->neurons[j]->weights[k]);
            fprintf(file, network->layers[i]->neurons[j + 1] ? "]\n\t\t\tbias: %lf\n\t\t},\n" : "]\n\t\t\tbias: %lf\n\t\t}\n", network->layers[i]->neurons[j]->bias);
        }
        fprintf(file, network->layers[i + 1] ? "\t},\n" : "\t}\n");
    }
    fprintf(file, "}");
    fclose(file);
    return (1);
}

network_t *load_network(char *filename)
{
    FILE *file;
    int input_height;
    int hidden_width;
    int hidden_height;
    int output_height;
    int previous_layer_height;
    network_t *network;

    file = fopen(filename, "r");
    if (!fscanf(file, "network:\n{\n\tinput_height: %d\n\thidden_width: %d\n\thidden_height: %d\n\toutput_height: %d\n\tlayers:\n", &input_height, &hidden_width, &hidden_height, &output_height))
    {
        fclose(file);
        return (NULL);
    }
    network = init_network(input_height, hidden_width, hidden_height, output_height);
    for (int i = 0; network->layers[i]; i++)
    {
        if (i == 0)
            previous_layer_height = 0;
        else if (i == 1)
            previous_layer_height = input_height;
        else
            previous_layer_height = hidden_height;
        for (int j = 0; network->layers[i]->neurons[j]; j++)
        {
            if (!fscanf(file, "%*[^-0-9]%lf", &network->layers[i]->neurons[j]->value))
            {
                fclose(file);
                free_network(network);
                return (NULL);
            }
            for (int k = 0; i != 0 && k < previous_layer_height; k++)
            {
                if (!fscanf(file, "%*[^-0-9]%lf", &network->layers[i]->neurons[j]->weights[k]))
                {
                    fclose(file);
                    free_network(network);
                    return (NULL);
                }
            }
            if (!fscanf(file, "%*[^-0-9]%lf", &network->layers[i]->neurons[j]->bias))
            {
                fclose(file);
                free_network(network);
                return (NULL);
            }
        }
    }
    fclose(file);
    return (network);
}