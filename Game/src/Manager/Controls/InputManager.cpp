#include "InputManager.h"

void InputManager::update(SDL_Event& event) {
    // Reset wheel
    wheelUp = false;
    wheelDown = false;

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
    } else if (event.type == SDL_MOUSEWHEEL) {
        if (event.wheel.y > 0) {
            wheelUp = true;
        } else if (event.wheel.y < 0) {
            wheelDown = true;
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

bool InputManager::isWheelUp() const { return wheelUp; }
bool InputManager::isWheelDown() const { return wheelDown; }

void InputManager::deactivateWheelUp() { wheelUp = false; }
void InputManager::deactivateWheelDown() { wheelDown = false; }