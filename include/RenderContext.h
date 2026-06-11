#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

struct SDL_Renderer;
class TextureManager;
class FontManager;

// Rendering systems handed to every Component::Render. Owned and wired
// by the Engine — components never touch globals.
struct RenderContext {
  SDL_Renderer *renderer = nullptr;
  TextureManager *textures = nullptr;
  FontManager *fonts = nullptr;
  bool debugDrawColliders = false;
};

#endif // RENDER_CONTEXT_H
