#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "neural-network.h"

#define HEIGHT 720
#define WIDTH 1280

void init_gui(network_t *network)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int quit;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Neural network", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        int x_step = WIDTH / (network->hidden_width + 2);
        int y_step = HEIGHT / network->hidden_height;
        int radius = 10;

        if (network->hidden_height > 10)
            radius = 10 / (network->hidden_height - 10);
        else if (network->hidden_width > 10)
            radius = 10 / (network->hidden_width - 10);
        for (int i = 0; i < network->input_height; i++)
        {
            int y = y_step * (i + 0.5) - (network->input_height * y_step / 2) + HEIGHT / 2;
            filledCircleColor(renderer, x_step / 2, y, radius, 0xFF0000FF);
        }
        for (int i = 0; i < network->hidden_width; i++)
        {
            for (int j = 0; j < network->hidden_height; j++)
            {
                int x = x_step * (i + 2) - (x_step / 2);
                int y = (j * y_step) + (y_step / 2);
                filledCircleColor(renderer, x, y, radius, 0xFF00FFFF);
            }
        }
        for (int i = 0; i < network->output_height; i++)
        {
            int y = (i * y_step) + (y_step / 2) + ((HEIGHT / 2) - ((network->output_height * y_step) / 2));
            filledCircleColor(renderer, x_step * (network->hidden_width + 2) - (x_step / 2), y, radius, 0xFF0000FF);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}