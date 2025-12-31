#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include <SDL2/SDL.h>

enum class ColliderType {
  STATIC,  // Immovable (walls, floors)
  DYNAMIC, // Moving (player, enemies, balls)
  TRIGGER  // Detects overlap but no physical response
};

class Collider : public Component {
public:
  Collider(int w, int h, ColliderType type = ColliderType::DYNAMIC);
  ~Collider() override = default;

  void SetDimensions(int w, int h);
  SDL_Rect GetBounds() const;

  void SetType(ColliderType t);
  ColliderType GetType() const;

  void SetBounciness(float b);
  float GetBounciness() const;

  // Setup for debug drawing
  static void SetDebugRenderer(SDL_Renderer *renderer);
  static void SetGlobalDebugDraw(bool draw);
  void Render() override;

private:
  int width;
  int height;
  ColliderType type;
  float bounciness; // 0.0 = no bounce, 1.0 = perfect energy conservation

  static SDL_Renderer *debugRenderer;
  static bool enableDebugDraw;
};

#endif // COLLIDER_H
