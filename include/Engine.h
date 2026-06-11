#ifndef ENGINE_H
#define ENGINE_H

#include "FontManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Physics.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>

// Engine startup options. All fields have sensible defaults, so
// Engine::Init() with no arguments behaves like before.
struct EngineConfig {
  std::string title = "2D Game Engine";
  int windowWidth = 800;
  int windowHeight = 600;
  int targetFPS = 60;

  // Physics advances in fixed steps of this size regardless of render
  // rate (deterministic simulation); rendering interpolates between the
  // last two physics states.
  float fixedTimeStep = 1.0f / 120.0f;

  // Key that quits the game. Set to SDLK_UNKNOWN to disable
  // (closing the window always quits).
  SDL_Keycode quitKey = SDLK_ESCAPE;

  // Draw green outlines around all colliders.
  bool debugDrawColliders = false;

  SDL_Color backgroundColor = {20, 20, 30, 255};

  // Upper bound on a single frame's deltaTime. Prevents a physics-step
  // avalanche after a long stall (window drag, breakpoint, system sleep).
  float maxDeltaTime = 0.05f;

  // Font file used by Text components. Empty = pick a system default.
  std::string fontPath;
};

class Engine {
public:
  Engine();
  ~Engine();

  bool Init(const EngineConfig &config = EngineConfig{});
  void Run();
  void Shutdown();
  void HandleEvents();
  void Update(float deltaTime);
  void Render(float alpha);

  // --- Scene management ---
  // Objects added or destroyed mid-frame are applied at the next frame
  // boundary, so iteration is never invalidated under your feet.
  GameObject *AddGameObject(std::unique_ptr<GameObject> gameObject);
  void Destroy(GameObject *gameObject);
  GameObject *FindGameObject(const std::string &name);
  const std::vector<std::unique_ptr<GameObject>> &GetGameObjects() const {
    return gameObjects;
  }

  // --- Systems ---
  InputManager *GetInput() { return &input; }
  TextureManager *GetTextures() { return textureManager.get(); }
  FontManager *GetFonts() { return fontManager.get(); }
  Physics *GetPhysics() { return physics.get(); }

  int GetWindowWidth() const { return config.windowWidth; }
  int GetWindowHeight() const { return config.windowHeight; }

private:
  void FlushPendingChanges();

  SDL_Window *window;
  SDL_Renderer *renderer;
  InputManager input;
  bool isRunning;
  bool hasShutdown;

  EngineConfig config;

  // GameObject system. pendingAdd holds objects spawned mid-frame until
  // the next FlushPendingChanges; destruction is mark-then-sweep.
  std::vector<std::unique_ptr<GameObject>> gameObjects;
  std::vector<std::unique_ptr<GameObject>> pendingAdd;

  // Systems
  std::unique_ptr<TextureManager> textureManager;
  std::unique_ptr<FontManager> fontManager;
  std::unique_ptr<Physics> physics;
};

#endif // ENGINE_H
