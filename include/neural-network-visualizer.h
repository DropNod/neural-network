#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <string.h>

#include "neural-network.h"

#define HEIGHT 720
#define WIDTH 1280

typedef struct coordinate_s
{
    int x;
    int y;
}   coordinate_t;
coordinate_t *init_coordinate(int x, int y);
void free_coordinate(coordinate_t *coordinate);


typedef struct visualizer_s
{
    network_t *network;
    coordinate_t ***coordinates;
    SDL_Window *window;
    SDL_Renderer *renderer;
}   visualizer_t;

visualizer_t *init_visualizer(network_t *network);
void free_visualizer(visualizer_t *visualizer);

void render(visualizer_t *visualizer);