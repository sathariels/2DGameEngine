#include "../include/FontManager.h"
#include <filesystem>
#include <iostream>

FontManager::~FontManager() { ClearCache(); }

bool FontManager::SetFontPath(const std::string &path) {
  if (!std::filesystem::exists(path)) {
    std::cerr << "FontManager: font file not found: " << path << "\n";
    return false;
  }
  fontPath = path;
  ClearCache();
  return true;
}

bool FontManager::UseDefaultSystemFont() {
  static const char *candidates[] = {
#if defined(__APPLE__)
      "/System/Library/Fonts/SFNSMono.ttf",
      "/System/Library/Fonts/Supplemental/Arial.ttf",
      "/System/Library/Fonts/Helvetica.ttc",
#elif defined(_WIN32)
      "C:\\Windows\\Fonts\\consola.ttf",
      "C:\\Windows\\Fonts\\arial.ttf",
      "C:\\Windows\\Fonts\\segoeui.ttf",
#else
      "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
      "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
      "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
      "/usr/share/fonts/TTF/DejaVuSans.ttf",
#endif
  };

  for (const char *path : candidates) {
    if (std::filesystem::exists(path)) {
      fontPath = path;
      ClearCache();
      return true;
    }
  }

  std::cerr << "FontManager: no system font found — text will not render. "
               "Call FontManager::SetFontPath with an explicit path.\n";
  return false;
}

TTF_Font *FontManager::GetFont(int size) {
  if (fontPath.empty())
    return nullptr;

  auto it = cache.find(size);
  if (it != cache.end())
    return it->second;

  TTF_Font *font = TTF_OpenFont(fontPath.c_str(), size);
  if (!font) {
    std::cerr << "TTF_OpenFont error (" << fontPath << " @ " << size
              << "pt): " << TTF_GetError() << "\n";
    return nullptr;
  }

  cache[size] = font;
  return font;
}

void FontManager::ClearCache() {
  for (auto &[size, font] : cache) {
    TTF_CloseFont(font);
  }
  cache.clear();
}
