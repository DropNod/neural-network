#include "neural-network.h"

int main()
{
    network_t *network;
    dataset_t *dataset;

    network = init_network(1, 2, 1000, 1);
    dataset = init_dataset("dataset.json");
    if (!network || !dataset)
        return (1);
    train(network, dataset, 10);
    free_network(network);
    return (0);
}