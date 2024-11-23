#include "InputManager.h"

void InputManager::update(SDL_Event& event) {
    // Mouse
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            isLeftClick = true;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
            isRightClick = true;
        }
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            isLeftClick = false;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
            isRightClick = false;
        }
    }

    // Keyboard
    if (event.type == SDL_KEYDOWN) {
        keys[event.key.keysym.sym] = true;
    } else if (event.type == SDL_KEYUP) {
        keys[event.key.keysym.sym] = false;
    }
}

bool InputManager::isKeyPressed(SDL_Keycode key) {
    return keys[key];
}

void InputManager::deactivateKey(SDL_Keycode key) {
    keys[key] = false;
}

bool InputManager::isLeftClicked() { return isLeftClick; }
bool InputManager::isRightClicked() { return isRightClick; }

void InputManager::deactivateLeftClick() { isLeftClick = false; }
void InputManager::deactivateRightClick() { isRightClick = false; }