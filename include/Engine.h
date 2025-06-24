#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "InputManager.h"
#include "GameObject.h"

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
    SDL_Renderer* renderer;
    InputManager input;
    bool isRunning;

    const int windowWidth = 800;
    const int windowHeight = 600;
    const int targetFPS = 60;

    // GameObject system
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    void CreateTestObjects();
    void RenderGameObject(GameObject* gameObject);
};

#endif // ENGINE_H