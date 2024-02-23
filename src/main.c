#include "neural-network.h"

int main()
{
    network_t *network;
    dataset_t *dataset;

    network = init_network(3, 10, 10, 3);
    init_gui(network);
    dataset = init_dataset("dataset.json");
    if (!network || !dataset)
        return (1);
    train(network, dataset, 10);
    free_network(network);
    return (0);
}