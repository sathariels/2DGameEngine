#include "../include/Physics.h"
#include "../include/Collider.h"
#include "../include/Rigidbody.h"
#include "../include/Transform.h"
#include <algorithm>
#include <cmath>

Physics::Physics() : gravity(980.0f) {}

void Physics::SetGravity(float g) { gravity = g; }
float Physics::GetGravity() const { return gravity; }

Physics::CollisionKey Physics::MakeKey(GameObject *a, GameObject *b) {
  unsigned int ia = a->GetID(), ib = b->GetID();
  return {std::min(ia, ib), std::max(ia, ib)};
}

void Physics::Update(float deltaTime,
                     std::vector<std::unique_ptr<GameObject>> &gameObjects) {
  // 1. Apply gravity and integrate velocity into position
  for (auto &obj : gameObjects) {
    if (!obj->IsActive()) continue;

    Rigidbody *rb        = obj->GetComponent<Rigidbody>();
    Transform *transform = obj->GetTransform();

    if (rb && transform) {
      rb->AddForce(0, gravity * rb->GetGravityScale() * rb->GetMass());
      Vector2 velocity = rb->GetVelocity();
      transform->Translate(velocity.x * deltaTime, velocity.y * deltaTime);
    }
  }

  // 2. Detect collisions, fire callbacks, resolve non-trigger pairs
  std::map<CollisionKey, CollisionPair> thisFrame;

  for (size_t i = 0; i < gameObjects.size(); ++i) {
    GameObject *objA = gameObjects[i].get();
    if (!objA->IsActive() || !objA->HasComponent<Collider>()) continue;

    for (size_t j = i + 1; j < gameObjects.size(); ++j) {
      GameObject *objB = gameObjects[j].get();
      if (!objB->IsActive() || !objB->HasComponent<Collider>()) continue;

      Collider *colA = objA->GetComponent<Collider>();
      Collider *colB = objB->GetComponent<Collider>();

      // Never resolve two statics
      bool aStatic  = (colA->GetType() == ColliderType::STATIC);
      bool bStatic  = (colB->GetType() == ColliderType::STATIC);
      bool aTrigger = (colA->GetType() == ColliderType::TRIGGER);
      bool bTrigger = (colB->GetType() == ColliderType::TRIGGER);

      if (aStatic && bStatic) continue;

      if (!AABB(colA->GetBounds(), colB->GetBounds())) continue;

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
      if (aTrigger || bTrigger) continue;

      ResolveCollision(objA, objB);
    }
  }

  // 3. Fire exit events for pairs that ended this frame
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

  // ---- Helper: elastic collision along one axis with restitution ----
  // Returns {newVa, newVb}
  auto elasticVelocities = [](float va, float vb, float ma, float mb, float cor)
      -> std::pair<float, float> {
    float totalMass = ma + mb;
    float newVa = (ma * va + mb * vb + mb * cor * (vb - va)) / totalMass;
    float newVb = (ma * va + mb * vb + ma * cor * (va - vb)) / totalMass;
    return {newVa, newVb};
  };

  if (overlapX < overlapY) {
    // ---- Resolve X ----
    float sign = (dx < 0) ? -1.0f : 1.0f;
    float push = overlapX * sign;

    if (!aStatic && bStatic) {
      transA->Translate(push, 0);
      if (rbA) rbA->SetVelocity(-rbA->GetVelocity().x * colA->GetBounciness(),
                                  rbA->GetVelocity().y);
    } else if (aStatic && !bStatic) {
      transB->Translate(-push, 0);
      if (rbB) rbB->SetVelocity(-rbB->GetVelocity().x * colB->GetBounciness(),
                                  rbB->GetVelocity().y);
    } else {
      // DYNAMIC vs DYNAMIC — proper momentum conservation
      transA->Translate(push * 0.5f, 0);
      transB->Translate(-push * 0.5f, 0);
      if (rbA && rbB) {
        float cor = std::min(colA->GetBounciness(), colB->GetBounciness());
        auto [newVax, newVbx] = elasticVelocities(
            rbA->GetVelocity().x, rbB->GetVelocity().x,
            rbA->GetMass(), rbB->GetMass(), cor);
        rbA->SetVelocity(newVax, rbA->GetVelocity().y);
        rbB->SetVelocity(newVbx, rbB->GetVelocity().y);
      }
    }
  } else {
    // ---- Resolve Y ----
    float sign = (dy < 0) ? -1.0f : 1.0f;
    float push = overlapY * sign;

    if (!aStatic && bStatic) {
      transA->Translate(0, push);
      if (rbA) rbA->SetVelocity(rbA->GetVelocity().x,
                                  -rbA->GetVelocity().y * colA->GetBounciness());
    } else if (aStatic && !bStatic) {
      transB->Translate(0, -push);
      if (rbB) rbB->SetVelocity(rbB->GetVelocity().x,
                                  -rbB->GetVelocity().y * colB->GetBounciness());
    } else {
      transA->Translate(0, push * 0.5f);
      transB->Translate(0, -push * 0.5f);
      if (rbA && rbB) {
        float cor = std::min(colA->GetBounciness(), colB->GetBounciness());
        auto [newVay, newVby] = elasticVelocities(
            rbA->GetVelocity().y, rbB->GetVelocity().y,
            rbA->GetMass(), rbB->GetMass(), cor);
        rbA->SetVelocity(rbA->GetVelocity().x, newVay);
        rbB->SetVelocity(rbB->GetVelocity().x, newVby);
      }
    }
  }
}
