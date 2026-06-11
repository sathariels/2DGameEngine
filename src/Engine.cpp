#include "../include/Engine.h"
#include "../include/GameObject.h"
#include "../include/RenderContext.h"
#include "../include/UpdateContext.h"
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <iostream>
#include <thread>

Engine::Engine()
    : window(nullptr), renderer(nullptr), isRunning(false),
      hasShutdown(false) {}

Engine::~Engine() { Shutdown(); }

bool Engine::Init(const EngineConfig &cfg) {
  config = cfg;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return false;
  }

  if (TTF_Init() != 0) {
    std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow(config.title.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, config.windowWidth,
                            config.windowHeight, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    return false;
  }

  // Engine-owned systems — handed to components via Update/RenderContext
  textureManager = std::make_unique<TextureManager>(renderer);
  physics = std::make_unique<Physics>();

  fontManager = std::make_unique<FontManager>();
  if (!config.fontPath.empty()) {
    fontManager->SetFontPath(config.fontPath);
  } else {
    fontManager->UseDefaultSystemFont();
  }

  isRunning = true;

  return true;
}

GameObject *Engine::AddGameObject(std::unique_ptr<GameObject> gameObject) {
  GameObject *ptr = gameObject.get();
  gameObject->SetEngine(this);
  pendingAdd.push_back(std::move(gameObject));
  return ptr;
}

void Engine::Destroy(GameObject *gameObject) {
  if (gameObject) {
    gameObject->MarkForDestroy();
  }
}

GameObject *Engine::FindGameObject(const std::string &name) {
  for (auto &obj : gameObjects) {
    if (!obj->IsPendingDestroy() && obj->GetName() == name) return obj.get();
  }
  for (auto &obj : pendingAdd) {
    if (!obj->IsPendingDestroy() && obj->GetName() == name) return obj.get();
  }
  return nullptr;
}

void Engine::FlushPendingChanges() {
  // Sweep destroyed objects: purge their physics pairs first (fires
  // OnCollisionExit on partners) so no dangling pointers survive
  for (auto &obj : gameObjects) {
    if (obj->IsPendingDestroy()) {
      physics->RemoveGameObject(obj.get());
    }
  }
  gameObjects.erase(
      std::remove_if(gameObjects.begin(), gameObjects.end(),
                     [](const std::unique_ptr<GameObject> &obj) {
                       return obj->IsPendingDestroy();
                     }),
      gameObjects.end());

  // Then bring in objects spawned since the last flush
  for (auto &obj : pendingAdd) {
    gameObjects.push_back(std::move(obj));
  }
  pendingAdd.clear();
}

void Engine::Run() {
  using clock = std::chrono::high_resolution_clock;
  const std::chrono::milliseconds frameDuration(1000 / config.targetFPS);
  const float fixedDt = config.fixedTimeStep;

  auto lastTime = clock::now();
  float accumulator = 0.0f;

  while (isRunning) {
    auto now = clock::now();
    float frameTime = std::chrono::duration<float>(now - lastTime).count();
    lastTime = now;

    frameTime = std::min(frameTime, config.maxDeltaTime);

    // Apply last frame's spawns/destroys at the frame boundary
    FlushPendingChanges();

    HandleEvents();

    // Physics advances in fixed-size steps (deterministic, stable at any
    // render rate); whatever time is left over stays in the accumulator
    // and the renderer interpolates it. See Fiedler, "Fix Your Timestep".
    accumulator += frameTime;
    while (accumulator >= fixedDt) {
      physics->Update(fixedDt, gameObjects);
      accumulator -= fixedDt;
    }

    // Game logic runs once per rendered frame with real frame time
    Update(frameTime);

    Render(accumulator / fixedDt);

    auto frameEnd = clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        frameEnd - now);
    if (elapsed < frameDuration) {
      std::this_thread::sleep_for(frameDuration - elapsed);
    }
  }
}

void Engine::HandleEvents() {
  input.Update();

  bool quitKeyHit = (config.quitKey != SDLK_UNKNOWN) &&
                    input.IsKeyPressed(config.quitKey);
  if (input.QuitRequested() || quitKeyHit) {
    isRunning = false;
  }
}

void Engine::Update(float deltaTime) {
  UpdateContext ctx;
  ctx.deltaTime = deltaTime;
  ctx.input = &input;

  for (auto &gameObject : gameObjects) {
    gameObject->Update(ctx);
  }
}

void Engine::Render(float alpha) {
  const SDL_Color &bg = config.backgroundColor;
  SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
  SDL_RenderClear(renderer);

  RenderContext ctx;
  ctx.renderer = renderer;
  ctx.textures = textureManager.get();
  ctx.fonts = fontManager.get();
  ctx.debugDrawColliders = config.debugDrawColliders;

  for (auto &gameObject : gameObjects) {
    if (gameObject->IsActive()) {
      gameObject->Render(ctx, alpha);
    }
  }

  SDL_RenderPresent(renderer);
}

void Engine::Shutdown() {
  // Safe to call multiple times (the destructor also calls it)
  if (hasShutdown)
    return;
  hasShutdown = true;
  isRunning = false;

  // Clear game objects before shutting down
  pendingAdd.clear();
  gameObjects.clear();

  // Clean up systems (fonts must close before TTF_Quit)
  physics.reset();
  fontManager.reset();
  textureManager.reset();

  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }

  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
  TTF_Quit();
  SDL_Quit();
}
