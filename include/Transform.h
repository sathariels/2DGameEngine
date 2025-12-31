#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include <SDL2/SDL_rect.h>

struct Vector2 {
  float x, y;

  Vector2(float x = 0, float y = 0) : x(x), y(y) {}

  Vector2 operator+(const Vector2 &other) const {
    return Vector2(x + other.x, y + other.y);
  }

  Vector2 operator-(const Vector2 &other) const {
    return Vector2(x - other.x, y - other.y);
  }

  Vector2 operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
  }
};

class Transform : public Component {
public:
  Transform();
  ~Transform() override = default;

  void SetPosition(float x, float y);
  void SetPosition(const Vector2 &position);
  Vector2 GetPosition() const;

  void SetRotation(float angle);
  float GetRotation() const;

  void SetScale(float x, float y);
  void SetScale(const Vector2 &scale);
  Vector2 GetScale() const;

  void Translate(float x, float y);
  void Rotate(float angle);

  // Helper to convert to SDL Rect for rendering
  SDL_Rect ToSDLRect(int width, int height) const;

private:
  Vector2 position;
  float rotation;
  Vector2 scale;
};

#endif // TRANSFORM_H
