#ifndef PHYSICS_H
#define PHYSICS_H

#include "GameObject.h"
#include <SDL2/SDL.h>
#include <cstdint>
#include <map>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

class Physics {
public:
  Physics();
  ~Physics() = default;

  void SetGravity(float g);
  float GetGravity() const;

  // Broadphase grid cell size in pixels. Works best around the size of a
  // typical collider; larger objects simply span multiple cells.
  void SetCellSize(float size);
  float GetCellSize() const;

  // Advances one fixed physics step: captures previous positions (for
  // render interpolation), integrates rigidbodies, then detects and
  // resolves collisions.
  void Update(float deltaTime,
              std::vector<std::unique_ptr<GameObject>> &gameObjects);

  // Forget an object that is being removed from the scene: erases its
  // active collision pairs and fires OnCollisionExit on its partners,
  // so no dangling pointers survive in activeCollisions.
  void RemoveGameObject(GameObject *obj);

private:
  float gravity;
  float cellSize;

  // Collision pair keyed by sorted object IDs (smaller ID first)
  using CollisionKey = std::pair<unsigned int, unsigned int>;
  using CollisionPair = std::pair<GameObject *, GameObject *>;
  std::map<CollisionKey, CollisionPair> activeCollisions;

  // Uniform spatial hash (broadphase). Rebuilt every step; kept as a
  // member so bucket allocations are reused across frames.
  std::unordered_map<std::uint64_t, std::vector<GameObject *>> grid;

  static CollisionKey MakeKey(GameObject *a, GameObject *b);
  static std::uint64_t CellKey(int cx, int cy);
  static std::uint64_t PairKey(GameObject *a, GameObject *b);

  void BuildGrid(std::vector<std::unique_ptr<GameObject>> &gameObjects);
  void TestPair(GameObject *objA, GameObject *objB,
                std::map<CollisionKey, CollisionPair> &thisFrame);

  bool AABB(const SDL_Rect &a, const SDL_Rect &b);
  void ResolveCollision(GameObject *a, GameObject *b);
};

#endif // PHYSICS_H
