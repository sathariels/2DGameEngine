#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <string>

// Forward declarations
class TextureManager;

class Sprite : public Component {
public:
  Sprite();
  ~Sprite() override = default;

  void SetTexture(SDL_Texture *texture);
  void SetDimensions(int width, int height);
  void SetColor(Uint8 r, Uint8 g, Uint8 b);

  void Render() override;

  // Static setters for engine systems
  static void SetRenderer(SDL_Renderer *renderer);
  static void SetTextureManager(TextureManager *manager);

private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Color color;

  static SDL_Renderer *renderer;
  static TextureManager *textureManager;
};

#endif // SPRITE_H
