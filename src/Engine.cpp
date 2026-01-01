#include "../include/Engine.h"
#include "../include/Collider.h"
#include "../include/GameObject.h"
#include "../include/InputManager.h"
#include "../include/Rigidbody.h"
#include "../include/Sprite.h"
#include "../include/Transform.h"
#include <iostream>
#include <thread>

Engine::Engine() : window(nullptr), renderer(nullptr), isRunning(false) {}

Engine::~Engine() { Shutdown(); }

bool Engine::Init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow("2D Game Engine with Sprites",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            windowWidth, windowHeight, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    return false;
  }

  // Initialize texture manager
  textureManager = std::make_unique<TextureManager>(renderer);

  // Initialize physics system
  physics = std::make_unique<Physics>();

  // Set static references for Sprite class
  Sprite::SetRenderer(renderer);
  Sprite::SetTextureManager(textureManager.get());

  // Set static references for Collider debug drawing
  Collider::SetDebugRenderer(renderer);
  Collider::SetGlobalDebugDraw(true); // Enable debug visualization

  isRunning = true;

  return true;
}

void Engine::AddGameObject(std::unique_ptr<GameObject> gameObject) {
  gameObjects.push_back(std::move(gameObject));
}

void Engine::Run() {
  using clock = std::chrono::high_resolution_clock;
  const std::chrono::milliseconds frameDuration(1000 / targetFPS);

  while (isRunning) {
    auto frameStart = clock::now();

    HandleEvents();
    Update(frameDuration.count() / 1000.0f);
    Render();

    auto frameEnd = clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        frameEnd - frameStart);
    if (elapsed < frameDuration) {
      std::this_thread::sleep_for(frameDuration - elapsed);
    }
  }
}

void Engine::HandleEvents() {
  input.Update();

  if (input.IsKeyPressed(SDLK_ESCAPE)) {
    isRunning = false;
  }
}

void Engine::Update(float deltaTime) {
  // Update physics system
  physics->Update(deltaTime, gameObjects);

  // Update all game objects
  for (auto &gameObject : gameObjects) {
    gameObject->Update(deltaTime);
  }

  // Handle global input
  if (input.IsKeyPressed(SDLK_ESCAPE)) {
    isRunning = false;
  }
}

void Engine::Render() {
  // Set background color
  SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
  SDL_RenderClear(renderer);

  // Render all game objects (they now use their Sprite components)
  for (auto &gameObject : gameObjects) {
    if (gameObject->IsActive()) {
      gameObject->Render(); // This will call Sprite::Render() for each object
    }
  }

  SDL_RenderPresent(renderer);
}

void Engine::Shutdown() {
  // Clear game objects before shutting down
  gameObjects.clear();

  // Clean up systems
  physics.reset();
  textureManager.reset();

  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }

  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
  SDL_Quit();
}