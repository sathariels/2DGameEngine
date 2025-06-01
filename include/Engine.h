#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include "InputManager.h"  // ✅ Add this line!

#include <chrono>

class Engine {
public:
    Engine();
    ~Engine();

    bool Init();
    void Run();
    void Shutdown();
    void HandleEvents();
    void Update(float deltaTime);
    void Render();


private:
    SDL_Window* window;
    SDL_Renderer* renderer;  // (optional, for future drawing)
    InputManager input;
    bool isRunning;

    const int windowWidth = 800;
    const int windowHeight = 600;
    const int targetFPS = 60;
};

#endif
