#ifndef TEXT_H
#define TEXT_H

#include "Component.h"
#include "RenderContext.h"
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
    void SetFontSize(int size);

    void Render(const RenderContext &ctx, float alpha) override;

private:
    std::string  text;
    SDL_Color    color;
    int          fontSize;
    bool         dirty;
    SDL_Texture *texture;
    TTF_Font    *lastFont; // detect font (re)loads between frames
    int          texW, texH;

    void rebuildTexture(const RenderContext &ctx, TTF_Font *font);
};

#endif // TEXT_H
