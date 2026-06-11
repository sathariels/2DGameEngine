#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL2/SDL.h>
#include <unordered_map>

class InputManager {
public:
    InputManager() = default;
    ~InputManager() = default;

    void Update();  // Call once per frame
    bool IsKeyPressed(SDL_Keycode key) const;
    bool IsKeyReleased(SDL_Keycode key) const;
    bool IsKeyHeld(SDL_Keycode key) const;

    // True once the window has been closed (SDL_QUIT)
    bool QuitRequested() const;

private:
    std::unordered_map<SDL_Keycode, bool> currentKeyState;
    std::unordered_map<SDL_Keycode, bool> previousKeyState;
    bool quitRequested = false;
};

#endif
