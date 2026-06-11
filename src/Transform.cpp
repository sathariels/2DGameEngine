#include "../include/Transform.h"

Transform::Transform()
    : position(0.0f, 0.0f), previousPosition(0.0f, 0.0f), rotation(0.0f),
      scale(1.0f, 1.0f) {}

void Transform::SetPosition(float x, float y) {
  SetPosition(Vector2(x, y));
}

void Transform::SetPosition(const Vector2 &pos) {
  position = pos;
  previousPosition = pos; // teleport — don't interpolate across it
}

Vector2 Transform::GetPosition() const { return position; }

void Transform::SetRotation(float angle) { rotation = angle; }

float Transform::GetRotation() const { return rotation; }

void Transform::SetScale(float x, float y) {
  scale.x = x;
  scale.y = y;
}

void Transform::SetScale(const Vector2 &s) { scale = s; }

Vector2 Transform::GetScale() const { return scale; }

void Transform::Translate(float x, float y) {
  position.x += x;
  position.y += y;
}

void Transform::Rotate(float angle) { rotation += angle; }

void Transform::CapturePreviousPosition() { previousPosition = position; }

Vector2 Transform::GetInterpolatedPosition(float alpha) const {
  return Vector2::Lerp(previousPosition, position, alpha);
}

SDL_Rect Transform::ToSDLRect(int width, int height) const {
  return ToSDLRect(width, height, position);
}

SDL_Rect Transform::ToSDLRect(int width, int height,
                              const Vector2 &pos) const {
  SDL_Rect rect;
  rect.h = static_cast<int>(height * scale.y);
  rect.w = static_cast<int>(width * scale.x);
  // Center the rect on the position
  rect.x = static_cast<int>(pos.x) - (rect.w / 2);
  rect.y = static_cast<int>(pos.y) - (rect.h / 2);
  return rect;
}
