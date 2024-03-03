#include "neural-network.h"

int save_network(network_t *network, char *filename)
{
    FILE *fd;

    fd = fopen(filename, "w");

    fprintf(fd, "network:\n{\n");
    fprintf(fd, "\tlayers:\n");
    for (int i = 0; network->layers[i]; i++)
    {
        fprintf(fd, "\t{\n");
        fprintf(fd, "\t\tneurons:\n");
        for (int j = 0; network->layers[i]->neurons[j]; j++)
        {
            fprintf(fd, "\t\t{\n");
            fprintf(fd, "\t\t\tvalue: %f\n", network->layers[i]->neurons[j]->value);
            fprintf(fd, "\t\t\tweights: [");
            for (int k = 0; network->layers[i]->neurons[j]->weights[k]; k++)
            {
                if (network->layers[i]->neurons[j]->weights[k + 1])
                    fprintf(fd, "%f, ", network->layers[i]->neurons[j]->weights[k]);
                else   
                    fprintf(fd, "%f", network->layers[i]->neurons[j]->weights[k]);
            }
            fprintf(fd, "]\n");
            fprintf(fd, "\t\t\tbias: %f\n", network->layers[i]->neurons[j]->bias);
            if (network->layers[i]->neurons[j + 1])
                fprintf(fd, "\t\t},\n");
            else
                fprintf(fd, "\t\t}\n");
        }
        if (network->layers[i + 1])
            fprintf(fd, "\t},\n");
        else
            fprintf(fd, "\t}\n");
    }
    fprintf(fd, "}");
}