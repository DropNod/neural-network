#include "neural-network.h"

int save_network(network_t *network, char *filename)
{
    FILE *file;
    int previous_size;

    file = fopen(filename, "w");
    fprintf(file, "network:\n{\n\tinput_height: %d\n\thidden_width: %d\n\thidden_height: %d\n\toutput_height: %d\n\tlayers:\n",
        network->input_height,
        network->hidden_width,
        network->hidden_height,
        network->output_height);
    for (int i = 0; network->layers[i]; i++)
    {
        fprintf(file, "\t{\n\t\tneurons:\n");
        int j = 0;
        for (; network->layers[i]->neurons[j]; j++)
        {
            fprintf(file, "\t\t{\n\t\t\tvalue: %f\n\t\t\tweights: [", network->layers[i]->neurons[j]->value);
            for (int k = 0; network->layers[i]->neurons[j]->weights[k]; k++)
            {
                if (network->layers[i]->neurons[j]->weights[k + 1])
                    fprintf(file, "%f, ", network->layers[i]->neurons[j]->weights[k]);
                else   
                    fprintf(file, "%f", network->layers[i]->neurons[j]->weights[k]);
            }
            if (network->layers[i]->neurons[j + 1])
                fprintf(file, "]\n\t\t\tbias: %f\n\t\t},\n", network->layers[i]->neurons[j]->bias);
            else
                fprintf(file, "]\n\t\t\tbias: %f\n\t\t}\n", network->layers[i]->neurons[j]->bias);
        }
        previous_size = j;
        if (network->layers[i + 1])
            fprintf(file, "\t},\n");
        else
            fprintf(file, "\t}\n");
    }
    fprintf(file, "}");
    fclose(file);
}

network_t *load_network(char *filename)
{
    FILE *file;
    int input_height;
    int hidden_width;
    int hidden_height;
    int output_height;
    int previous_size;
    network_t *network;

    file = fopen(filename, "r");
    if (!fscanf(file, "network:\n{\n\tinput_height: %d\n\thidden_width: %d\n\thidden_height: %d\n\toutput_height: %d\n\tlayers:\n", &input_height, &hidden_width, &hidden_height, &output_height))
    {
        printf("1\n");
        fclose(file);
        return (NULL);
    }
    network = init_network(input_height, hidden_width, hidden_height, output_height);
    previous_size = 0;
    for (int i = 0; network->layers[i]; i++)
    {
        int j = 0;
        for (; network->layers[i]->neurons[j]; j++)
        {
            if (!fscanf(file, "%*[^0-9]%f", &network->layers[i]->neurons[j]->value))
            {
                printf("2\n");
                fclose(file);
                free_network(network);
                return (NULL);
            }
            for (int k = 0; k < previous_size; k++)
            {
                if (!fscanf(file, "%*[^0-9]%f", &network->layers[i]->neurons[j]->weights[k]))
                {
                    printf("3\n");
                    fclose(file);
                    free_network(network);
                    return (NULL);
                }
            }
            if (!fscanf(file, "%*[^0-9]%f", &network->layers[i]->neurons[j]->bias))
            {
                printf("4\n");
                fclose(file);
                free_network(network);
                return (NULL);
            }
        }
        previous_size = j;
    }
    fclose(file);
    return (network);
}