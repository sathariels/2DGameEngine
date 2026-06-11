#include "../include/InputManager.h"

void InputManager::Update() {
    // Save the previous key state
    previousKeyState = currentKeyState;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quitRequested = true;
                break;

            case SDL_KEYDOWN:
                if (event.key.repeat == 0) {
                    currentKeyState[event.key.keysym.sym] = true;
                }
                break;

            case SDL_KEYUP:
                currentKeyState[event.key.keysym.sym] = false;
                break;

            default:
                break;
        }
    }
}

bool InputManager::QuitRequested() const {
    return quitRequested;
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
