#ifndef ENGINE_H
#define ENGINE_H

#include "GameObject.h"
#include "InputManager.h"
#include "Physics.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

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

  // Game Object Management
  void AddGameObject(std::unique_ptr<GameObject> gameObject);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  InputManager input;
  bool isRunning;

  const int windowWidth = 800;
  const int windowHeight = 600;
  const int targetFPS = 60;

  // GameObject system
  std::vector<std::unique_ptr<GameObject>> gameObjects;

  // Rendering system
  std::unique_ptr<TextureManager> textureManager;

  // Physics system
  std::unique_ptr<Physics> physics;
};

#endif // ENGINE_H