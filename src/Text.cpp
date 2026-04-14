#include "../include/Text.h"
#include "../include/GameObject.h"
#include "../include/Transform.h"
#include <iostream>

SDL_Renderer *Text::renderer = nullptr;
TTF_Font     *Text::font     = nullptr;

Text::Text(const std::string &text, int fontSize)
    : text(text), fontSize(fontSize), dirty(true),
      texture(nullptr), texW(0), texH(0) {
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

void Text::SetRenderer(SDL_Renderer *r) { renderer = r; }

bool Text::LoadFont(const std::string &path, int size) {
    CloseFont();
    font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        std::cerr << "TTF_OpenFont error (" << path << "): " << TTF_GetError() << "\n";
        return false;
    }
    return true;
}

void Text::CloseFont() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

void Text::rebuildTexture() {
    if (!font || !renderer || text.empty()) return;

    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "TTF_RenderText error: " << TTF_GetError() << "\n";
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    texW    = surface->w;
    texH    = surface->h;
    SDL_FreeSurface(surface);
}

void Text::Render() {
    if (!IsActive() || !renderer || !owner) return;

    if (dirty || !texture) {
        rebuildTexture();
        dirty = false;
    }
    if (!texture) return;

    Transform *t = owner->GetTransform();
    if (!t) return;

    Vector2  pos = t->GetPosition();
    SDL_Rect dst = {
        (int)(pos.x - texW / 2.0f),
        (int)(pos.y - texH / 2.0f),
        texW, texH
    };
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}
