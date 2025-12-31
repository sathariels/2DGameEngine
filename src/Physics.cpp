#include "Physics.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Transform.h"
#include <algorithm>
#include <cmath>
#include <iostream>

Physics::Physics()
    : gravity(980.0f) { // 980 pixels per second squared (roughly 9.8 m/s * 100
                        // pixels/m)
}

void Physics::SetGravity(float g) { gravity = g; }

float Physics::GetGravity() const { return gravity; }

void Physics::Update(float deltaTime,
                     std::vector<std::unique_ptr<GameObject>> &gameObjects) {
  // 1. Apply gravity and move objects
  for (auto &obj : gameObjects) {
    if (!obj->IsActive())
      continue;

    Rigidbody *rb = obj->GetComponent<Rigidbody>();
    Transform *transform = obj->GetTransform();

    if (rb && transform) {
      // Apply gravity
      rb->AddForce(0, gravity * rb->GetGravityScale() * rb->GetMass());

      // Move based on velocity
      Vector2 velocity = rb->GetVelocity();
      transform->Translate(velocity.x * deltaTime, velocity.y * deltaTime);
    }
  }

  // 2. Detect and resolve collisions
  // Simple O(N^2) check for now
  for (size_t i = 0; i < gameObjects.size(); ++i) {
    GameObject *objA = gameObjects[i].get();
    if (!objA->IsActive() || !objA->HasComponent<Collider>())
      continue;

    for (size_t j = i + 1; j < gameObjects.size(); ++j) {
      GameObject *objB = gameObjects[j].get();
      if (!objB->IsActive() || !objB->HasComponent<Collider>())
        continue;

      Collider *colA = objA->GetComponent<Collider>();
      Collider *colB = objB->GetComponent<Collider>();

      // Static-Static collisions don't need resolution
      if (colA->GetType() == ColliderType::STATIC &&
          colB->GetType() == ColliderType::STATIC)
        continue;

      if (AABB(colA->GetBounds(), colB->GetBounds())) {
        ResolveCollision(objA, objB);
      }
    }
  }
}

bool Physics::AABB(const SDL_Rect &a, const SDL_Rect &b) {
  return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h &&
          a.y + a.h > b.y);
}

void Physics::ResolveCollision(GameObject *a, GameObject *b) {
  Collider *colA = a->GetComponent<Collider>();
  Collider *colB = b->GetComponent<Collider>();
  Rigidbody *rbA = a->GetComponent<Rigidbody>();
  Rigidbody *rbB = b->GetComponent<Rigidbody>();
  Transform *transA = a->GetTransform();
  Transform *transB = b->GetTransform();

  SDL_Rect rectA = colA->GetBounds();
  SDL_Rect rectB = colB->GetBounds();

  // Calculate overlap
  float overlapX = 0;
  float overlapY = 0;

  // Center distance
  float dx = (rectA.x + rectA.w / 2.0f) - (rectB.x + rectB.w / 2.0f);
  float dy = (rectA.y + rectA.h / 2.0f) - (rectB.y + rectB.h / 2.0f);

  // Combined half widths/heights
  float combinedHalfW = (rectA.w + rectB.w) / 2.0f;
  float combinedHalfH = (rectA.h + rectB.h) / 2.0f;

  if (std::abs(dx) < combinedHalfW) {
    overlapX = combinedHalfW - std::abs(dx);
  }

  if (std::abs(dy) < combinedHalfH) {
    overlapY = combinedHalfH - std::abs(dy);
  }

  // If overlaps are small/zero, nothing to do
  if (overlapX <= 0 || overlapY <= 0)
    return; // Should have been caught by AABB check but safe to double check

  // Resolve along axis of least penetration
  if (overlapX < overlapY) {
    // Resolve X
    int sign = (dx < 0) ? -1 : 1;
    float resolveDist = overlapX * sign;

    // Push objects apart
    if (colA->GetType() == ColliderType::DYNAMIC &&
        colB->GetType() == ColliderType::STATIC) {
      transA->Translate(resolveDist, 0);
      if (rbA)
        rbA->SetVelocity(-rbA->GetVelocity().x * colA->GetBounciness(),
                         rbA->GetVelocity().y);
    } else if (colA->GetType() == ColliderType::STATIC &&
               colB->GetType() == ColliderType::DYNAMIC) {
      transB->Translate(-resolveDist, 0);
      if (rbB)
        rbB->SetVelocity(-rbB->GetVelocity().x * colB->GetBounciness(),
                         rbB->GetVelocity().y);
    } else if (colA->GetType() == ColliderType::DYNAMIC &&
               colB->GetType() == ColliderType::DYNAMIC) {
      transA->Translate(resolveDist * 0.5f, 0);
      transB->Translate(-resolveDist * 0.5f, 0);

      // Should properly conserve momentum but simple bounce for now
      if (rbA)
        rbA->SetVelocity(-rbA->GetVelocity().x * colA->GetBounciness(),
                         rbA->GetVelocity().y);
      if (rbB)
        rbB->SetVelocity(-rbB->GetVelocity().x * colB->GetBounciness(),
                         rbB->GetVelocity().y);
    }
  } else {
    // Resolve Y
    int sign = (dy < 0) ? -1 : 1;
    float resolveDist = overlapY * sign;

    if (colA->GetType() == ColliderType::DYNAMIC &&
        colB->GetType() == ColliderType::STATIC) {
      transA->Translate(0, resolveDist);
      if (rbA) {
        // Ground check logic often goes here
        rbA->SetVelocity(rbA->GetVelocity().x,
                         -rbA->GetVelocity().y * colA->GetBounciness());
      }
    } else if (colA->GetType() == ColliderType::STATIC &&
               colB->GetType() == ColliderType::DYNAMIC) {
      transB->Translate(0, -resolveDist);
      if (rbB)
        rbB->SetVelocity(rbB->GetVelocity().x,
                         -rbB->GetVelocity().y * colB->GetBounciness());
    } else if (colA->GetType() == ColliderType::DYNAMIC &&
               colB->GetType() == ColliderType::DYNAMIC) {
      transA->Translate(0, resolveDist * 0.5f);
      transB->Translate(0, -resolveDist * 0.5f);

      if (rbA)
        rbA->SetVelocity(rbA->GetVelocity().x,
                         -rbA->GetVelocity().y * colA->GetBounciness());
      if (rbB)
        rbB->SetVelocity(rbB->GetVelocity().x,
                         -rbB->GetVelocity().y * colB->GetBounciness());
    }
  }
}

float Physics::Clamp(float value, float min, float max) {
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}
