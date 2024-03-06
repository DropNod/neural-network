#include "neural-network.h"
#include "neural-network-visualizer.h"
#include <pthread.h>

void *train_thread(void *arg)
{
    network_t *network;
    dataset_t *dataset;

    network = (network_t *) arg;
    dataset = init_dataset("dataset.json");
    train(network, dataset, 1000000);
    pthread_exit(NULL);
}


int main()
{
    network_t *network;
    //visualizer_t *visualizer;
    pthread_t thread_id;

    network = init_network(3, 10, 10, 3);
    save_network(network, "test");
    free_network(network);
    network = load_network("test");
    if (!network)
        return (1);
    save_network(network, "test2");
    // visualizer = init_visualizer(network);
    // pthread_create(&thread_id, NULL, train_thread, network);
    // render(visualizer);
    // free_visualizer(visualizer);
    // pthread_join(thread_id, NULL);
    free_network(network);
    return (0);
}