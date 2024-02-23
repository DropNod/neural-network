#include "neural-network-visualizer.h"

coordinate_t *init_coordinate(int x, int y)
{
    coordinate_t *coordinate;

    coordinate = malloc(sizeof(coordinate_t));
    coordinate->x = x;
    coordinate->y = y;
    return (coordinate);
}

void free_coordinate(coordinate_t *coordinate)
{
    free(coordinate);
}