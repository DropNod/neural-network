#include "neural-network.h"

dataset_t *init_dataset(const char *path)
{
    dataset_t *dataset;
    FILE *file;

    dataset = full_calloc(sizeof(dataset_t));
    if (!dataset)
        return (NULL);
    file = fopen(path, "r");
    if (!file)
        return (free(dataset), NULL);
    if (!fscanf(file, "%*[^-0-9]%zu%*[^-0-9]%zu%*[^-0-9]%zu", &dataset->size, &dataset->input_size, &dataset->output_size))
        return (free(dataset), NULL);
    dataset->input = full_calloc(dataset->size * sizeof(double *));
    dataset->output = full_calloc(dataset->size * sizeof(double *));
    if (!dataset->input || !dataset->output)
        return (free_dataset(dataset), NULL);
    for (size_t i = 0; i < dataset->size; i++)
    {
        dataset->input[i] = full_calloc(dataset->input_size * sizeof(double));
        if (!dataset->input[i])
            return (free_dataset(dataset), NULL);
        for (size_t j = 0; j < dataset->input_size; j++)
            if (!fscanf(file, "%*[^-0-9]%lf", &dataset->input[i][j]))
                return (free_dataset(dataset), NULL);
    }
    for (size_t i = 0; i < dataset->size; i++)
    {
        dataset->output[i] = full_calloc(dataset->output_size * sizeof(double));
        if (!dataset->output[i])
            return (free_dataset(dataset), NULL);
        for (size_t j = 0; j < dataset->output_size; j++)
            if (!fscanf(file, "%*[^-0-9]%lf", &dataset->output[i][j]))
                return (free_dataset(dataset), NULL);
    }
    fclose(file);
    return (dataset);
}

void free_dataset(dataset_t *dataset)
{
    if (dataset)
    {
        for (size_t i = 0; i < dataset->size; i++)
        {
            secure_free(dataset->input[i]);
            secure_free(dataset->output[i]);
        }
        secure_free(dataset->input);
        secure_free(dataset->output);
        free(dataset);
    }
}