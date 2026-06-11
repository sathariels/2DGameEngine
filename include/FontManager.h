#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

// Owns TTF fonts, opened lazily per point size and cached. Replaces the
// old single static font in Text — every Text component can now use its
// own size from the same font file.
class FontManager {
public:
  FontManager() = default;
  ~FontManager();

  FontManager(const FontManager &) = delete;
  FontManager &operator=(const FontManager &) = delete;

  // Use a specific font file for all Text components. Clears the cache.
  bool SetFontPath(const std::string &path);

  // Try a list of well-known system font paths for the current platform
  // (macOS / Linux / Windows). Returns false if none exist.
  bool UseDefaultSystemFont();

  // Returns the font at the given size, opening and caching it on first
  // use. Returns nullptr if no font path has been set / found.
  TTF_Font *GetFont(int size);

  const std::string &GetFontPath() const { return fontPath; }

private:
  void ClearCache();

  std::string fontPath;
  std::unordered_map<int, TTF_Font *> cache;
};

#endif // FONT_MANAGER_H
