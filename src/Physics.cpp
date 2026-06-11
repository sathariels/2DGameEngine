#include "../include/Physics.h"
#include "../include/Collider.h"
#include "../include/Rigidbody.h"
#include "../include/Transform.h"
#include <algorithm>
#include <cmath>
#include <unordered_set>

Physics::Physics() : gravity(980.0f), cellSize(128.0f) {}

void Physics::SetGravity(float g) { gravity = g; }
float Physics::GetGravity() const { return gravity; }

void Physics::SetCellSize(float size) { cellSize = std::max(1.0f, size); }
float Physics::GetCellSize() const { return cellSize; }

Physics::CollisionKey Physics::MakeKey(GameObject *a, GameObject *b) {
  unsigned int ia = a->GetID(), ib = b->GetID();
  return {std::min(ia, ib), std::max(ia, ib)};
}

std::uint64_t Physics::CellKey(int cx, int cy) {
  return (static_cast<std::uint64_t>(static_cast<std::uint32_t>(cx)) << 32) |
         static_cast<std::uint32_t>(cy);
}

std::uint64_t Physics::PairKey(GameObject *a, GameObject *b) {
  std::uint32_t ia = a->GetID(), ib = b->GetID();
  if (ia > ib) std::swap(ia, ib);
  return (static_cast<std::uint64_t>(ia) << 32) | ib;
}

void Physics::Update(float deltaTime,
                     std::vector<std::unique_ptr<GameObject>> &gameObjects) {
  // 1. Capture step-start positions so the renderer can interpolate
  //    between the previous and current physics state
  for (auto &obj : gameObjects) {
    if (!obj->IsActive()) continue;
    if (Transform *transform = obj->GetTransform())
      transform->CapturePreviousPosition();
  }

  // 2. Apply gravity, integrate forces into velocity, then velocity
  //    into position (semi-implicit Euler, all in one place)
  for (auto &obj : gameObjects) {
    if (!obj->IsActive()) continue;

    Rigidbody *rb        = obj->GetComponent<Rigidbody>();
    Transform *transform = obj->GetTransform();

    if (rb && transform && rb->IsActive()) {
      rb->AddForce(0, gravity * rb->GetGravityScale() * rb->GetMass());
      rb->Integrate(deltaTime);
      Vector2 velocity = rb->GetVelocity();
      transform->Translate(velocity.x * deltaTime, velocity.y * deltaTime);
    }
  }

  // 3. Broadphase: bin colliders into a uniform spatial hash, then only
  //    test pairs that share a cell — O(n + pairs) instead of O(n²)
  BuildGrid(gameObjects);

  std::map<CollisionKey, CollisionPair> thisFrame;
  std::unordered_set<std::uint64_t> tested; // pairs can share many cells

  for (auto &[cell, objects] : grid) {
    for (size_t i = 0; i < objects.size(); ++i) {
      for (size_t j = i + 1; j < objects.size(); ++j) {
        if (!tested.insert(PairKey(objects[i], objects[j])).second) continue;
        TestPair(objects[i], objects[j], thisFrame);
      }
    }
  }

  // 4. Fire exit events for pairs that ended this frame
  for (auto &[key, pair] : activeCollisions) {
    if (thisFrame.find(key) == thisFrame.end()) {
      if (pair.first->IsActive() && pair.second->IsActive()) {
        pair.first->OnCollisionExit(pair.second);
        pair.second->OnCollisionExit(pair.first);
      }
    }
  }

  activeCollisions = thisFrame;
}

void Physics::BuildGrid(
    std::vector<std::unique_ptr<GameObject>> &gameObjects) {
  for (auto &[cell, objects] : grid)
    objects.clear();

  for (auto &obj : gameObjects) {
    if (!obj->IsActive()) continue;

    Collider *col = obj->GetComponent<Collider>();
    if (!col || !col->IsActive()) continue;

    SDL_Rect b = col->GetBounds();
    int minX = static_cast<int>(std::floor(b.x / cellSize));
    int maxX = static_cast<int>(std::floor((b.x + b.w) / cellSize));
    int minY = static_cast<int>(std::floor(b.y / cellSize));
    int maxY = static_cast<int>(std::floor((b.y + b.h) / cellSize));

    for (int cy = minY; cy <= maxY; ++cy)
      for (int cx = minX; cx <= maxX; ++cx)
        grid[CellKey(cx, cy)].push_back(obj.get());
  }
}

void Physics::TestPair(GameObject *objA, GameObject *objB,
                       std::map<CollisionKey, CollisionPair> &thisFrame) {
  Collider *colA = objA->GetComponent<Collider>();
  Collider *colB = objB->GetComponent<Collider>();

  bool aStatic  = (colA->GetType() == ColliderType::STATIC);
  bool bStatic  = (colB->GetType() == ColliderType::STATIC);
  bool aTrigger = (colA->GetType() == ColliderType::TRIGGER);
  bool bTrigger = (colB->GetType() == ColliderType::TRIGGER);

  // Never resolve two statics
  if (aStatic && bStatic) return;

  if (!AABB(colA->GetBounds(), colB->GetBounds())) return;

  // Record and fire enter/stay
  CollisionKey key = MakeKey(objA, objB);
  thisFrame[key]   = {objA, objB};

  bool isNew = (activeCollisions.find(key) == activeCollisions.end());
  if (isNew) {
    objA->OnCollisionEnter(objB);
    objB->OnCollisionEnter(objA);
  } else {
    objA->OnCollisionStay(objB);
    objB->OnCollisionStay(objA);
  }

  // Triggers only notify — no positional resolution
  if (aTrigger || bTrigger) return;

  ResolveCollision(objA, objB);
}

void Physics::RemoveGameObject(GameObject *obj) {
  for (auto it = activeCollisions.begin(); it != activeCollisions.end();) {
    auto &[a, b] = it->second;
    if (a == obj || b == obj) {
      GameObject *partner = (a == obj) ? b : a;
      if (partner->IsActive()) partner->OnCollisionExit(obj);
      it = activeCollisions.erase(it);
    } else {
      ++it;
    }
  }
}

bool Physics::AABB(const SDL_Rect &a, const SDL_Rect &b) {
  return (a.x < b.x + b.w && a.x + a.w > b.x &&
          a.y < b.y + b.h && a.y + a.h > b.y);
}

void Physics::ResolveCollision(GameObject *a, GameObject *b) {
  Collider  *colA   = a->GetComponent<Collider>();
  Collider  *colB   = b->GetComponent<Collider>();
  Rigidbody *rbA    = a->GetComponent<Rigidbody>();
  Rigidbody *rbB    = b->GetComponent<Rigidbody>();
  Transform *transA = a->GetTransform();
  Transform *transB = b->GetTransform();

  SDL_Rect rectA = colA->GetBounds();
  SDL_Rect rectB = colB->GetBounds();

  float dx = (rectA.x + rectA.w / 2.0f) - (rectB.x + rectB.w / 2.0f);
  float dy = (rectA.y + rectA.h / 2.0f) - (rectB.y + rectB.h / 2.0f);

  float combinedHalfW = (rectA.w + rectB.w) / 2.0f;
  float combinedHalfH = (rectA.h + rectB.h) / 2.0f;

  float overlapX = combinedHalfW - std::abs(dx);
  float overlapY = combinedHalfH - std::abs(dy);

  if (overlapX <= 0 || overlapY <= 0) return;

  bool aStatic = (colA->GetType() == ColliderType::STATIC);
  bool bStatic = (colB->GetType() == ColliderType::STATIC);

  // Collision normal: unit vector pointing from B toward A along the
  // axis of least penetration
  Vector2 normal;
  float depth;
  if (overlapX < overlapY) {
    normal = Vector2((dx < 0) ? -1.0f : 1.0f, 0.0f);
    depth  = overlapX;
  } else {
    normal = Vector2(0.0f, (dy < 0) ? -1.0f : 1.0f);
    depth  = overlapY;
  }
  Vector2 push = normal * depth;

  // Reflect with restitution: scales only the normal component of the
  // velocity, leaving the tangential component untouched:
  //   v' = v - (1 + e)(v . n) n
  // Skipped when the body is already separating, so a lingering overlap
  // can't flip the velocity back and forth.
  auto bounce = [](Rigidbody *rb, const Vector2 &n, float e) {
    Vector2 v  = rb->GetVelocity();
    float   vn = v.Dot(n);
    if (vn >= 0.0f) return;
    rb->SetVelocity(v - n * ((1.0f + e) * vn));
  };

  if (!aStatic && bStatic) {
    transA->Translate(push.x, push.y);
    if (rbA) bounce(rbA, normal, colA->GetBounciness());
  } else if (aStatic && !bStatic) {
    transB->Translate(-push.x, -push.y);
    if (rbB) bounce(rbB, -normal, colB->GetBounciness());
  } else {
    // DYNAMIC vs DYNAMIC — split separation, conserve momentum along
    // the collision normal (1-D elastic collision with restitution)
    transA->Translate(push.x * 0.5f, push.y * 0.5f);
    transB->Translate(-push.x * 0.5f, -push.y * 0.5f);

    if (rbA && rbB) {
      Vector2 va = rbA->GetVelocity();
      Vector2 vb = rbB->GetVelocity();
      float van = va.Dot(normal);
      float vbn = vb.Dot(normal);

      // Only respond if they are approaching along the normal
      if (van - vbn < 0.0f) {
        float cor = std::min(colA->GetBounciness(), colB->GetBounciness());
        float ma = rbA->GetMass(), mb = rbB->GetMass();
        float totalMass = ma + mb;

        float newVan = (ma * van + mb * vbn + mb * cor * (vbn - van)) / totalMass;
        float newVbn = (ma * van + mb * vbn + ma * cor * (van - vbn)) / totalMass;

        rbA->SetVelocity(va + normal * (newVan - van));
        rbB->SetVelocity(vb + normal * (newVbn - vbn));
      }
    }
  }
}
