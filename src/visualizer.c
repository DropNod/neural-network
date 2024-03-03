#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "neural-network-visualizer.h"

visualizer_t *init_visualizer(network_t *network)
{
    visualizer_t *visualizer;
    int x_step;
    int y_step;

    visualizer = malloc(sizeof(visualizer_t));
    if (!visualizer)
        return (NULL);
    visualizer->network = network;
    visualizer->coordinates = malloc((network->hidden_width + 3) * sizeof(coordinate_t **));
    visualizer->coordinates[0] = malloc((network->input_height + 1) * sizeof(coordinate_t *));
    x_step = WIDTH / (network->hidden_width + 2);
    y_step = HEIGHT / network->hidden_height;
    for (int i = 0; i < network->input_height; i++)
        visualizer->coordinates[0][i] = init_coordinate(x_step / 2, y_step * (i + 0.5) - (network->input_height * y_step / 2) + HEIGHT / 2);
    visualizer->coordinates[0][network->input_height] = NULL;
    for (int i = 1; i < network->hidden_width + 1; i++)
    {
        visualizer->coordinates[i] = malloc((network->hidden_height + 1) * sizeof(coordinate_t *));
        for (int j = 0; j < network->hidden_height; j++)
            visualizer->coordinates[i][j] = init_coordinate(x_step * (i + 1) - (x_step / 2), (j * y_step) + (y_step / 2));
        visualizer->coordinates[i][network->hidden_height] = NULL;
    }
    visualizer->coordinates[network->hidden_width + 1] = malloc((network->output_height + 1) * sizeof(coordinate_t *));
    for (int i = 0; i < network->output_height; i++)
        visualizer->coordinates[network->hidden_width + 1][i] = init_coordinate(x_step * (network->hidden_width + 2) - (x_step / 2), (i * y_step) + (y_step / 2) + ((HEIGHT / 2) - ((network->output_height * y_step) / 2)));
    visualizer->coordinates[network->hidden_width + 1][network->output_height] = NULL;
    visualizer->window = SDL_CreateWindow("Neural network", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    visualizer->renderer = SDL_CreateRenderer(visualizer->window, -1, SDL_RENDERER_ACCELERATED);
    visualizer->height = HEIGHT;
    visualizer->width = WIDTH;
    return (visualizer);
}

void free_visualizer(visualizer_t *visualizer)
{
    for (int i = 0; visualizer->coordinates[i]; i++)
    {
        for (int j = 0; visualizer->coordinates[i][j]; j++)
            free_coordinate(visualizer->coordinates[i][j]);
        free(visualizer->coordinates[i]);
    }
    free(visualizer->coordinates);
    SDL_DestroyRenderer(visualizer->renderer);
    SDL_DestroyWindow(visualizer->window);
    SDL_Quit();
}

void render(visualizer_t *visualizer)
{

    int quit;
    SDL_Event event;
    char tmp[17];
    int radius;
    coordinate_t origin = {0, 0};
    coordinate_t mouse_click_coords;
    coordinate_t previous_mouse_coords;
    coordinate_t mouse_coords;
    int mouse_click_state;
    float zoom;

    quit = 0;
    radius = 10;
    mouse_click_state = 0;
    zoom = 1.0;
    if (visualizer->network->hidden_height > 10)
        radius = 10 / (visualizer->network->hidden_height - 10);
    else if (visualizer->network->hidden_width > 10)
        radius = 10 / (visualizer->network->hidden_width - 10);
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        mouse_click_state = 1;
                        SDL_GetMouseState(&mouse_click_coords.x, &mouse_click_coords.y);
                        mouse_click_coords.x -= origin.x;
                        mouse_click_coords.y -= origin.y;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        mouse_click_state = 0;
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    if (event.wheel.y > 0)
                        zoom *= 1.01;
                    else if (event.wheel.y < 0)
                        zoom *= 0.99;
                    break;
            }
        }
        if (mouse_click_state) 
        {
            SDL_GetMouseState(&mouse_coords.x, &mouse_coords.y);
            origin.x = mouse_coords.x -  mouse_click_coords.x;
            origin.y = mouse_coords.y -  mouse_click_coords.y;
            previous_mouse_coords.x = mouse_coords.x;
            previous_mouse_coords.y = mouse_coords.y;
        }
        SDL_SetRenderDrawColor(visualizer->renderer, 0, 0, 0, 255);
        SDL_RenderClear(visualizer->renderer);
        for (int i = 0; visualizer->coordinates[i]; i++)
        {
            for (int j = 0; visualizer->coordinates[i][j]; j++)
            {
                for (int k = 0; i < visualizer->network->hidden_width + 1 && visualizer->coordinates[i + 1][k]; k++)
                    lineRGBA(visualizer->renderer, zoom * (origin.x + visualizer->coordinates[i][j]->x), zoom * (origin.y + visualizer->coordinates[i][j]->y), zoom * (origin.x + visualizer->coordinates[i + 1][k]->x), zoom * (origin.y + visualizer->coordinates[i + 1][k]->y), 255, 255, 255, (visualizer->network->layers[i + 1]->neurons[k]->weights[j] + 0.1) * 5 * 75);
                filledCircleColor(visualizer->renderer, zoom * (origin.x + visualizer->coordinates[i][j]->x), zoom * (origin.y + visualizer->coordinates[i][j]->y), zoom * radius, 0x7D0000FF);
                sprintf(tmp, "%f", visualizer->network->layers[i]->neurons[j]->value);
                stringRGBA(visualizer->renderer, zoom * (origin.x + visualizer->coordinates[i][j]->x - 35), zoom * (origin.y + visualizer->coordinates[i][j]->y - 10 - radius), tmp, 255, 255, 255, 255);
            }
        }
        SDL_RenderPresent(visualizer->renderer);
    }
}


// void init_gui(network_t *network)
// {
//     SDL_Window *window = NULL;
//     SDL_Renderer *renderer = NULL;
//     int quit;
//     SDL_Event event;

//     SDL_Init(SDL_INIT_VIDEO);
//     window = SDL_CreateWindow("Neural network", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
//     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     quit = 0;
//     while (!quit) {
//         while (SDL_PollEvent(&event) != 0) {
//             if (event.type == SDL_QUIT) {
//                 quit = 1;
//             }
//         }
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderClear(renderer);

//         int x_step = WIDTH / (network->hidden_width + 2);
//         int y_step = HEIGHT / network->hidden_height;
//         int radius = 10;

//         if (network->hidden_height > 10)
//             radius = 10 / (network->hidden_height - 10);
//         else if (network->hidden_width > 10)
//             radius = 10 / (network->hidden_width - 10);
//         for (int i = 0; i < network->input_height; i++)
//         {
//             int y = y_step * (i + 0.5) - (network->input_height * y_step / 2) + HEIGHT / 2;
//             filledCircleColor(renderer, x_step / 2, y, radius, 0xFF0000FF);
//         }
//         for (int i = 0; i < network->hidden_width; i++)
//         {
//             for (int j = 0; j < network->hidden_height; j++)
//             {
//                 int x = x_step * (i + 2) - (x_step / 2);
//                 int y = (j * y_step) + (y_step / 2);
//                 filledCircleColor(renderer, x, y, radius, 0xFF00FFFF);
//             }
//         }
//         for (int i = 0; i < network->output_height; i++)
//         {
//             int y = (i * y_step) + (y_step / 2) + ((HEIGHT / 2) - ((network->output_height * y_step) / 2));
//             filledCircleColor(renderer, x_step * (network->hidden_width + 2) - (x_step / 2), y, radius, 0xFF0000FF);
//         }
//         SDL_RenderPresent(renderer);
//     }

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }