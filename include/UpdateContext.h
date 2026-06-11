#ifndef UPDATE_CONTEXT_H
#define UPDATE_CONTEXT_H

class InputManager;

// Per-frame state handed to every Component::Update. Systems are passed
// in explicitly (dependency injection) instead of being reached through
// global singletons, which keeps components testable and the engine's
// wiring visible in one place (Engine::Update).
struct UpdateContext {
  float deltaTime = 0.0f;
  InputManager *input = nullptr;
};

#endif // UPDATE_CONTEXT_H
