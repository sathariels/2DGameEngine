#include "../include/Sprite.h"
#include "../include/GameObject.h"
#include "../include/Transform.h"

Sprite::Sprite() : texture(nullptr), width(0), height(0), color({255, 255, 255, 255}) {}

void Sprite::SetColor(Uint8 r, Uint8 g, Uint8 b) {
  color = {r, g, b, 255};
}

void Sprite::SetTexture(SDL_Texture *tex) {
  texture = tex;
  if (texture) {
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  }
}

void Sprite::SetDimensions(int w, int h) {
  width = w;
  height = h;
}

void Sprite::Render(const RenderContext &ctx, float alpha) {
  if (!IsActive() || !ctx.renderer || !owner)
    return;

  Transform *transform = owner->GetTransform();
  if (!transform)
    return;

  // Blend between the last two physics states for smooth motion at any
  // render rate (fixed-timestep interpolation)
  Vector2 pos = transform->GetInterpolatedPosition(alpha);
  SDL_Rect dstRect = transform->ToSDLRect(width, height, pos);

  if (texture) {
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
    SDL_RenderCopyEx(ctx.renderer, texture, nullptr, &dstRect,
                     transform->GetRotation(), nullptr, SDL_FLIP_NONE);
  } else {
    SDL_SetRenderDrawColor(ctx.renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(ctx.renderer, &dstRect);
  }
}
