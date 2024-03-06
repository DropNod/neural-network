#include "neural-network.h"
#include "neural-network-visualizer.h"
#include <pthread.h>

void *train_thread(void *arg)
{
    network_t *network;
    dataset_t *dataset;

    network = (network_t *) arg;
    dataset = init_dataset("dataset");
    if (!dataset)
        return (error("Can't init dataset"), NULL);
    if (!train(network, dataset, 100000000))
        return (error("Can't train network"), NULL);
    free_dataset(dataset);
    pthread_exit(NULL);
}


int main()
{
    network_t *network;
    dataset_t *dataset;
    visualizer_t *visualizer;
    pthread_t thread_id;

    network = init_network(1, 1, 5, 1);
    if (!network)
        return (error("Can't init network"), 1);
    save_network(network, "save");
    visualizer = init_visualizer(network);
    pthread_create(&thread_id, NULL, train_thread, network);
    render(visualizer);
    free_visualizer(visualizer);
    pthread_join(thread_id, NULL);
    free_network(network);
    return (0);
}