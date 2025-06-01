#include "Engine.h"
#include <iostream>
#include <thread>
#include "InputManager.h"


Engine::Engine() : window(nullptr), isRunning(false) {}

Engine::~Engine() {
    Shutdown();
}

bool Engine::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "2D Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    isRunning = true;
    return true;
}

#include "InputManager.h"

void Engine::Run() {
    using clock = std::chrono::high_resolution_clock;
    const std::chrono::milliseconds frameDuration(1000 / targetFPS);

    while (isRunning) {
        auto frameStart = clock::now();

        HandleEvents();           // 👈 Clean input section
        Update(frameDuration.count() / 1000.0f);  // 👈 Pass delta time in seconds
        Render();                 // 👈 Placeholder for now

        auto frameEnd = clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
        if (elapsed < frameDuration) {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
    }
}

void Engine::HandleEvents() {
    input.Update(); // from your InputManager

    if (input.IsKeyPressed(SDLK_ESCAPE)) {
        isRunning = false;
    }
}
void Engine::Update(float deltaTime) {
    // TODO: Game logic (movement, physics, etc.)
    // Example: player.position += velocity * deltaTime;
}
void Engine::Render() {
    // TODO: Clear screen, draw everything, present frame
    // SDL_RenderClear(renderer);
    // SDL_RenderCopy(renderer, ...);
    // SDL_RenderPresent(renderer);
}









void Engine::Shutdown() {
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}
