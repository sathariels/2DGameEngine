#include "../include/Text.h"
#include "../include/FontManager.h"
#include "../include/GameObject.h"
#include "../include/Transform.h"
#include <iostream>

Text::Text(const std::string &text, int fontSize)
    : text(text), fontSize(fontSize), dirty(true),
      texture(nullptr), lastFont(nullptr), texW(0), texH(0) {
    color = {255, 255, 255, 255};
}

Text::~Text() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Text::SetText(const std::string &t) {
    if (text == t) return;
    text  = t;
    dirty = true;
}

const std::string &Text::GetText() const { return text; }

void Text::SetColor(Uint8 r, Uint8 g, Uint8 b) {
    color = {r, g, b, 255};
    dirty = true;
}

void Text::SetFontSize(int size) {
    if (fontSize == size) return;
    fontSize = size;
    dirty    = true;
}

void Text::rebuildTexture(const RenderContext &ctx, TTF_Font *font) {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    if (!font || text.empty()) return;

    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "TTF_RenderText error: " << TTF_GetError() << "\n";
        return;
    }

    texture = SDL_CreateTextureFromSurface(ctx.renderer, surface);
    texW    = surface->w;
    texH    = surface->h;
    SDL_FreeSurface(surface);
}

void Text::Render(const RenderContext &ctx, float alpha) {
    if (!IsActive() || !ctx.renderer || !ctx.fonts || !owner) return;

    TTF_Font *font = ctx.fonts->GetFont(fontSize);
    if (dirty || !texture || font != lastFont) {
        rebuildTexture(ctx, font);
        lastFont = font;
        dirty    = false;
    }
    if (!texture) return;

    Transform *t = owner->GetTransform();
    if (!t) return;

    Vector2  pos = t->GetInterpolatedPosition(alpha);
    SDL_Rect dst = {
        (int)(pos.x - texW / 2.0f),
        (int)(pos.y - texH / 2.0f),
        texW, texH
    };
    SDL_RenderCopy(ctx.renderer, texture, nullptr, &dst);
}
