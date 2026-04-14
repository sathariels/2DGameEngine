#ifndef TEXT_H
#define TEXT_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Text : public Component {
public:
    explicit Text(const std::string &text = "", int fontSize = 22);
    ~Text() override;

    void SetText(const std::string &text);
    const std::string &GetText() const;
    void SetColor(Uint8 r, Uint8 g, Uint8 b);

    void Render() override;

    // Call once before using any Text component (Engine::Init does this)
    static void SetRenderer(SDL_Renderer *r);

    // Call after engine.Init() to choose the font file and size
    static bool LoadFont(const std::string &path, int size = 22);
    static void CloseFont();

private:
    std::string  text;
    SDL_Color    color;
    int          fontSize;
    bool         dirty;
    SDL_Texture *texture;
    int          texW, texH;

    void rebuildTexture();

    static SDL_Renderer *renderer;
    static TTF_Font     *font;
};

#endif // TEXT_H
