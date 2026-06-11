#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"
#include "RenderContext.h"
#include <SDL2/SDL.h>

class Sprite : public Component {
public:
  Sprite();
  ~Sprite() override = default;

  void SetTexture(SDL_Texture *texture);
  void SetDimensions(int width, int height);
  void SetColor(Uint8 r, Uint8 g, Uint8 b);

  void Render(const RenderContext &ctx, float alpha) override;

private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Color color;
};

#endif // SPRITE_H
