#include "../include/Sprite.h"
#include "../include/GameObject.h"
#include "../include/TextureManager.h"
#include "../include/Transform.h"
#include <iostream>

SDL_Renderer *Sprite::renderer = nullptr;
TextureManager *Sprite::textureManager = nullptr;

Sprite::Sprite() : texture(nullptr), width(0), height(0), color({255, 255, 255, 255}) {}

void Sprite::SetColor(Uint8 r, Uint8 g, Uint8 b) {
  color = {r, g, b, 255};
}

void Sprite::SetRenderer(SDL_Renderer *r) { renderer = r; }

void Sprite::SetTextureManager(TextureManager *tm) { textureManager = tm; }

void Sprite::SetTexture(SDL_Texture *tex) {
  texture = tex;
  if (texture && textureManager) {
    textureManager->GetTextureDimensions(texture, width, height);
  }
}

void Sprite::SetDimensions(int w, int h) {
  width = w;
  height = h;
}

void Sprite::Render() {
  if (!IsActive() || !renderer || !owner)
    return;

  Transform *transform = owner->GetTransform();
  if (!transform)
    return;

  SDL_Rect dstRect = transform->ToSDLRect(width, height);

  if (texture) {
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
    SDL_RenderCopyEx(renderer, texture, nullptr, &dstRect,
                     transform->GetRotation(), nullptr, SDL_FLIP_NONE);
  } else {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &dstRect);
  }
}
