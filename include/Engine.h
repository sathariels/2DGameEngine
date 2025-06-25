#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "InputManager.h"
#include "GameObject.h"
#include "TextureManager.h"

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

    // Rendering system
    std::unique_ptr<TextureManager> textureManager;

    // Methods
    void CreateTestObjects();
    void RenderGameObject(GameObject* gameObject);
    void CreateTestSprites(); // New method for sprite examples
};

#endif // ENGINE_H