#include "../include/TextureManager.h"
#include <iostream>

TextureManager::TextureManager(SDL_Renderer *renderer) : renderer(renderer) {}

TextureManager::~TextureManager() { ClearCache(); }

SDL_Texture *TextureManager::CreateColorTexture(int width, int height, Uint8 r,
                                                Uint8 g, Uint8 b, Uint8 a) {
  // Generate a unique key for this color texture
  std::string key = "color_" + std::to_string(width) + "x" +
                    std::to_string(height) + "_" + std::to_string(r) + "_" +
                    std::to_string(g) + "_" + std::to_string(b) + "_" +
                    std::to_string(a);

  // Check if we already have it cached
  if (textureCache.find(key) != textureCache.end()) {
    return textureCache[key];
  }

  SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  if (!surface) {
    std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, r, g, b, a));

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (texture) {
    textureCache[key] = texture;
  }

  return texture;
}

bool TextureManager::GetTextureDimensions(SDL_Texture *texture, int &width,
                                          int &height) {
  if (!texture)
    return false;
  return SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) == 0;
}

void TextureManager::ClearCache() {
  for (auto &pair : textureCache) {
    SDL_DestroyTexture(pair.second);
  }
  textureCache.clear();
}

size_t TextureManager::GetCacheSize() const { return textureCache.size(); }

SDL_Texture *TextureManager::CreateGradientTexture(int width, int height,
                                                   Uint8 r1, Uint8 g1, Uint8 b1,
                                                   Uint8 r2, Uint8 g2,
                                                   Uint8 b2) {
  std::string key = "grad_" + std::to_string(width) + "x" +
                    std::to_string(height) + "_" + std::to_string(r1) + "," +
                    std::to_string(g1) + "," + std::to_string(b1) + "_" +
                    std::to_string(r2) + "," + std::to_string(g2) + "," +
                    std::to_string(b2);

  if (textureCache.find(key) != textureCache.end()) {
    return textureCache[key];
  }

  SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  if (!surface)
    return nullptr;

  // Simple vertical gradient
  for (int y = 0; y < height; ++y) {
    float ratio = static_cast<float>(y) / height;
    Uint8 r = static_cast<Uint8>(r1 * (1.0f - ratio) + r2 * ratio);
    Uint8 g = static_cast<Uint8>(g1 * (1.0f - ratio) + g2 * ratio);
    Uint8 b = static_cast<Uint8>(b1 * (1.0f - ratio) + b2 * ratio);

    SDL_Rect line = {0, y, width, 1};
    SDL_FillRect(surface, &line, SDL_MapRGB(surface->format, r, g, b));
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (texture) {
    textureCache[key] = texture;
  }

  return texture;
}

SDL_Texture *TextureManager::CreateCheckeredTexture(int width, int height,
                                                    Uint8 r1, Uint8 g1,
                                                    Uint8 b1, Uint8 r2,
                                                    Uint8 g2, Uint8 b2) {
  // For simplicity, just use color texture for now, or implement actual
  // checkerboard if needed This is just a placeholder to satisfy the header
  return CreateGradientTexture(width, height, r1, g1, b1, r2, g2, b2);
}
