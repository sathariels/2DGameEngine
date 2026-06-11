#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "Vector2.h"
#include <SDL2/SDL_rect.h>

class Transform : public Component {
public:
  Transform();
  ~Transform() override = default;

  // SetPosition is a teleport: it moves the previous position too, so
  // the renderer never interpolates across the jump.
  void SetPosition(float x, float y);
  void SetPosition(const Vector2 &position);
  Vector2 GetPosition() const;

  void SetRotation(float angle);
  float GetRotation() const;

  void SetScale(float x, float y);
  void SetScale(const Vector2 &scale);
  Vector2 GetScale() const;

  // Continuous motion — used by physics integration. Only moves the
  // current position so rendering can interpolate from the previous one.
  void Translate(float x, float y);
  void Rotate(float angle);

  // Fixed-timestep interpolation support. The Physics system captures
  // the position at the start of each step; the renderer blends between
  // that and the current position by alpha (0..1).
  void CapturePreviousPosition();
  Vector2 GetInterpolatedPosition(float alpha) const;

  // Helpers to convert to SDL Rect for rendering (centered on pos)
  SDL_Rect ToSDLRect(int width, int height) const;
  SDL_Rect ToSDLRect(int width, int height, const Vector2 &pos) const;

private:
  Vector2 position;
  Vector2 previousPosition;
  float rotation;
  Vector2 scale;
};

#endif // TRANSFORM_H
