#include "neural-network.h"

dataset_t *init_dataset(char *path)
{
    // Ouvrir le fichier JSON
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return (NULL);
    }

    // Lire le contenu du fichier
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *json_string = (char *)malloc(file_size + 1);
    if (json_string == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        fclose(file);
        return (NULL);
    }
    fread(json_string, 1, file_size, file);
    json_string[file_size] = '\0'; // Terminer la chaîne par un caractère nul
    fclose(file);

    // Parse le JSON
    cJSON *root = cJSON_Parse(json_string);
    if (root == NULL) {
        printf("Erreur de parsing JSON.\n");
        free(json_string);
        return (NULL);
    }

    // Initialisation du dataset
    dataset_t *dataset;
    dataset = malloc(sizeof(dataset_t));
    dataset->size = cJSON_GetArraySize(root);
    dataset->input = malloc(dataset->size * sizeof(double *));
    dataset->output = malloc(dataset->size * sizeof(double *));
    if (dataset->input == NULL || dataset->output == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        cJSON_Delete(root);
        free(json_string);
        return (NULL);
    }

    // Parcours des éléments du tableau
    int i = 0;
    cJSON *item;
    cJSON_ArrayForEach(item, root) {
        cJSON *input = cJSON_GetObjectItemCaseSensitive(item, "input");
        cJSON *output = cJSON_GetObjectItemCaseSensitive(item, "output");

        // Vérification et stockage des données
        if (cJSON_IsArray(input) && cJSON_IsArray(output)) {
            cJSON *input_element = cJSON_GetArrayItem(input, 0);
            cJSON *output_element = cJSON_GetArrayItem(output, 0);

            if (cJSON_IsNumber(input_element) && cJSON_IsNumber(output_element)) {
                // Allocation et stockage des données dans le dataset
                dataset->input[i] = malloc(sizeof(double));
                dataset->output[i] = malloc(sizeof(double));
                if (dataset->input[i] == NULL || dataset->output[i] == NULL) {
                    printf("Erreur d'allocation mémoire.\n");
                    free_dataset(dataset);
                    cJSON_Delete(root);
                    free(json_string);
                    return (NULL);
                }
                dataset->input[i][0] = input_element->valuedouble;
                dataset->output[i][0] = output_element->valuedouble;
                i++;
            }
        }
    }
    return (dataset);
}

void free_dataset(dataset_t *dataset)
{
    for (size_t j = 0; j < dataset->size; j++)
    {
        free(dataset->input[j]);
        free(dataset->output[j]);
    }
    free(dataset->input);
    free(dataset->output);
    free(dataset);
}