#pragma once

#include "neural-network.h"

#define HEIGHT 720
#define WIDTH 1280

typedef struct coordinate_s
{
    int x;
    int y;
}   coordinate_t;

typedef struct visualizer_s
{
    coordinate_t **coordinates;
}   visualizer_t;

void init_visualizer(network_t *network);