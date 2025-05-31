#include <SDL2/SDL.h>
#include <iostream>

int main() {
    // 1. Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 2. Create Window
    SDL_Window* window = SDL_CreateWindow(
        "2D Game Engine",                // Title
        SDL_WINDOWPOS_CENTERED,         // x position
        SDL_WINDOWPOS_CENTERED,         // y position
        800, 600,                        // Width, Height
        SDL_WINDOW_SHOWN                // Flags
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // 3. Main Loop
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Optional: Rendering goes here

        SDL_Delay(16); // Simulate 60 FPS (~16 ms/frame)
    }

    // 4. Clean Up
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
