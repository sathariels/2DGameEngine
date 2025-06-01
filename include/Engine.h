#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <chrono>

class Engine {
public:
    Engine();
    ~Engine();

    bool Init();
    void Run();
    void Shutdown();

private:
    SDL_Window* window;
    bool isRunning;

    const int windowWidth = 800;
    const int windowHeight = 600;
    const int targetFPS = 60;
};

#endif
