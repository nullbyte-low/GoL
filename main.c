#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include "patterns.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define CELL_SIZE 8
#define GRID_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)

void DrawGrid(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 31, 31, 31, 255);
    for (int i = 0; i < GRID_WIDTH; ++i)
    {
        for (int j = 0; j < GRID_HEIGHT; ++j)
        {
            SDL_FRect cell = {(float)(i * CELL_SIZE), (float)(j * CELL_SIZE), CELL_SIZE, CELL_SIZE};
            SDL_RenderRect(renderer, &cell);
        }
    }
}

void GoLTick(SDL_Renderer *renderer, int grid[GRID_WIDTH * GRID_HEIGHT]) {
    int update_buffer[GRID_WIDTH * GRID_HEIGHT] = {0};

    for (int i = 0; i < GRID_WIDTH; ++i)
    {
        for (int j = 0; j < GRID_HEIGHT; ++j)
        {
            int current_cell = grid[i + GRID_WIDTH * j];
            int neighbours_count = 0;
            for (int k = i - 1; k <= i + 1; ++k)
            {
                if (k < 0 || k >= GRID_WIDTH) { continue; }
                for (int l = j - 1; l <= j + 1; ++l)
                {
                    if (l < 0 || l >= GRID_HEIGHT) { continue; }
                    if (k == i && l == j) { continue; }

                    int current_neighbour = grid[k + GRID_WIDTH * l];
                    if (current_neighbour == 1) { neighbours_count++; }
                }
            }

            if (current_cell) {
                if (neighbours_count == 2 || neighbours_count == 3) {
                    update_buffer[i + GRID_WIDTH * j] = 1;
                } else {
                    update_buffer[i + GRID_WIDTH * j] = 0;
                }
            } else {
                if (neighbours_count == 3) {
                    update_buffer[i + GRID_WIDTH * j] = 1;
                } else {
                    update_buffer[i + GRID_WIDTH * j] = 0;
                }
            }

        }
    }

    for (int i = 0; i < GRID_WIDTH; ++i)
    {
        for (int j = 0; j < GRID_HEIGHT; ++j)
        {
            grid[i + GRID_WIDTH * j] = update_buffer[i + GRID_WIDTH * j];
        }
    }
}

void DrawCells(SDL_Renderer *renderer, int grid[GRID_WIDTH * GRID_HEIGHT]) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < GRID_WIDTH; ++i)
    {
        for (int j = 0; j < GRID_HEIGHT; ++j)
        {
            if (grid[i + GRID_WIDTH * j] == 0) { continue; }

            SDL_FRect cell = {
                .x = (float) (i * CELL_SIZE),
                .y = (float) (j * CELL_SIZE),
                .w = CELL_SIZE,
                .h = CELL_SIZE
            };

            SDL_RenderFillRect(renderer, &cell);
        }
    }
}

void SpawnEntity(int *grid, int grid_width, int grid_height, int start_x, int start_y, const CellOffset *pattern, size_t pattern_size) {
    for (size_t i = 0; i < pattern_size; ++i) {
        int target_x = start_x + pattern[i].dx;
        int target_y = start_y + pattern[i].dy;

        // Boundary check to make sure we don't spawn outside the grid array
        if (target_x >= 0 && target_x < grid_width && target_y >= 0 && target_y < grid_height) {
            grid[target_x + grid_width * target_y] = 1;
        }
    }
}

int main(int argc, char* argv[]) {
    // 1. Initialize SDL Video
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return 1;
    }

    // 2. Create a window (SDL3 merges creation functions and handles undefined positioning by default)
    SDL_Window* window = SDL_CreateWindow("Conway's GoL", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int grid[GRID_WIDTH * GRID_HEIGHT] = {0};

    // Spawn the engine at (10, 10)
    SpawnEntity(grid, GRID_WIDTH, GRID_HEIGHT, 10, 10, GLIDER_GUN, GLIDER_GUN_SIZE);
    SpawnEntity(grid, GRID_WIDTH, GRID_HEIGHT, 45, 35, DIEHARD, DIEHARD_SIZE);
    SpawnEntity(grid, GRID_WIDTH, GRID_HEIGHT, 50, 57, INFINITE_GROWTH, INFINITE_GROWTH_SIZE);

    // 3. Main loop 
    bool quit = false;
    SDL_Event event;

    int frame_count = 0;
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        frame_count++;
        if (frame_count >= 5) {
            GoLTick(renderer, grid);
            frame_count = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        DrawCells(renderer, grid);
        DrawGrid(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // 4. Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
} // gcc main.c -o bin/main `pkg-config --cflags --libs sdl3` && ./bin/main