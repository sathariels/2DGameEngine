#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>

class TextureManager {
public:
    TextureManager(SDL_Renderer* renderer);
    ~TextureManager();

    // Load a texture from file (caches automatically) - NOT IMPLEMENTED YET
    // SDL_Texture* LoadTexture(const std::string& filePath);

    // Get a previously loaded texture - NOT IMPLEMENTED YET
    // SDL_Texture* GetTexture(const std::string& filePath);

    // Create a colored rectangle texture (useful for prototyping)
    SDL_Texture* CreateColorTexture(int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

    // Get texture dimensions
    bool GetTextureDimensions(SDL_Texture* texture, int& width, int& height);
    // bool GetTextureDimensions(const std::string& filePath, int& width, int& height); // NOT IMPLEMENTED

    // Clear all cached textures
    void ClearCache();

    // Get cache statistics
    size_t GetCacheSize() const;


    // Create patterns for more visual variety
    SDL_Texture* CreateGradientTexture(int width, int height, Uint8 r1, Uint8 g1, Uint8 b1, Uint8 r2, Uint8 g2, Uint8 b2);
    SDL_Texture* CreateCheckeredTexture(int width, int height, Uint8 r1, Uint8 g1, Uint8 b1, Uint8 r2, Uint8 g2, Uint8 b2);

private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> textureCache;
};

#endif // TEXTUREMANAGER_H