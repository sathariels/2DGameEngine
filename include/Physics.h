#ifndef PHYSICS_H
#define PHYSICS_H

#include "GameObject.h"
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <utility>
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

  // Collision pair keyed by sorted object IDs (smaller ID first)
  using CollisionKey = std::pair<unsigned int, unsigned int>;
  using CollisionPair = std::pair<GameObject *, GameObject *>;
  std::map<CollisionKey, CollisionPair> activeCollisions;

  CollisionKey MakeKey(GameObject *a, GameObject *b);

  bool AABB(const SDL_Rect &a, const SDL_Rect &b);
  void ResolveCollision(GameObject *a, GameObject *b);
};

#endif // PHYSICS_H
