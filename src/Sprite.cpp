#include "Sprite.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Transform.h"
#include <iostream>

SDL_Renderer *Sprite::renderer = nullptr;
TextureManager *Sprite::textureManager = nullptr;

Sprite::Sprite() : texture(nullptr), width(0), height(0) {}

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
    SDL_RenderCopyEx(renderer, texture, nullptr, &dstRect,
                     transform->GetRotation(), nullptr, SDL_FLIP_NONE);
  } else {
    // Render a placeholder if no texture
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Magenta
    SDL_RenderFillRect(renderer, &dstRect);
  }
}
