#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL2/SDL.h>
#include <unordered_map>

class InputManager {
public:
    InputManager();
    ~InputManager() = default;

    void Update();  // Call once per frame
    bool IsKeyPressed(SDL_Keycode key) const;
    bool IsKeyReleased(SDL_Keycode key) const;
    bool IsKeyHeld(SDL_Keycode key) const;

private:
    std::unordered_map<SDL_Keycode, bool> currentKeyState;
    std::unordered_map<SDL_Keycode, bool> previousKeyState;
};

#endif
