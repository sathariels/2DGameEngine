#include "../include/Collider.h"
#include "../include/GameObject.h"
#include "../include/Transform.h"

SDL_Renderer *Collider::debugRenderer = nullptr;
bool Collider::enableDebugDraw = false;

Collider::Collider(int w, int h, ColliderType type)
    : width(w), height(h), type(type), bounciness(0.0f) {}

void Collider::SetDimensions(int w, int h) {
  width = w;
  height = h;
}

SDL_Rect Collider::GetBounds() const {
  SDL_Rect rect = {0, 0, width, height};

  if (owner) {
    Transform *transform = owner->GetTransform();
    if (transform) {
      // Recalculate based on position which is center
      Vector2 pos = transform->GetPosition();
      rect.x = static_cast<int>(pos.x) - (width / 2);
      rect.y = static_cast<int>(pos.y) - (height / 2);
    }
  }

  return rect;
}

void Collider::SetType(ColliderType t) { type = t; }

ColliderType Collider::GetType() const { return type; }

void Collider::SetBounciness(float b) { bounciness = b; }

float Collider::GetBounciness() const { return bounciness; }

void Collider::SetDebugRenderer(SDL_Renderer *renderer) {
  debugRenderer = renderer;
}

void Collider::SetGlobalDebugDraw(bool draw) { enableDebugDraw = draw; }

void Collider::Render() {
  if (!enableDebugDraw || !debugRenderer || !IsActive())
    return;

  SDL_Rect bounds = GetBounds();
  SDL_SetRenderDrawColor(debugRenderer, 0, 255, 0, 255); // Green outline
  SDL_RenderDrawRect(debugRenderer, &bounds);
}
