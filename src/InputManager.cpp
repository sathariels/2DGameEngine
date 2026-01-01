#include "../include/InputManager.h"
#include <iostream>

InputManager::InputManager() {}

void InputManager::Update() {
    // Save the previous key state
    previousKeyState = currentKeyState;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                // You can set a flag here if you want to handle quitting
                    currentKeyState[SDLK_ESCAPE] = true;  // optional shortcut
            break;

            case SDL_KEYDOWN:
                if (event.key.repeat == 0) {
                    SDL_Keycode key = event.key.keysym.sym;
                    currentKeyState[key] = true;
                    std::cout << "Key pressed: " << SDL_GetKeyName(key) << std::endl;
                }
            break;

            case SDL_KEYUP: {
                SDL_Keycode key = event.key.keysym.sym;
                currentKeyState[key] = false;
                std::cout << "Key released: " << SDL_GetKeyName(key) << std::endl;
                break;
            }

            default:
                break;
        }
    }
}

bool InputManager::IsKeyPressed(SDL_Keycode key) const {
    auto now = currentKeyState.find(key);
    auto prev = previousKeyState.find(key);

    bool isNow = (now != currentKeyState.end()) ? now->second : false;
    bool wasPrev = (prev != previousKeyState.end()) ? prev->second : false;

    return isNow && !wasPrev;
}

bool InputManager::IsKeyReleased(SDL_Keycode key) const {
    auto now = currentKeyState.find(key);
    auto prev = previousKeyState.find(key);

    bool isNow = (now != currentKeyState.end()) ? now->second : false;
    bool wasPrev = (prev != previousKeyState.end()) ? prev->second : false;

    return !isNow && wasPrev;
}

bool InputManager::IsKeyHeld(SDL_Keycode key) const {
    auto it = currentKeyState.find(key);
    return (it != currentKeyState.end()) ? it->second : false;
}
