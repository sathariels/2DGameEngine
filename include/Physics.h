#ifndef PHYSICS_H
#define PHYSICS_H

#include "GameObject.h"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

class Physics {
public:
  Physics();
  ~Physics() = default;

  void SetGravity(float g);
  float GetGravity() const;

  void Update(float deltaTime,
              std::vector<std::unique_ptr<GameObject>> &gameObjects);

private:
  float gravity;

  // Detect collision between two rectangles
  bool AABB(const SDL_Rect &a, const SDL_Rect &b);

  // Resolve collision between two objects
  void ResolveCollision(GameObject *a, GameObject *b);

  // Helper to clamp values
  float Clamp(float value, float min, float max);
};

#endif // PHYSICS_H
