#include "InputManager.h"
#include "../../Misc/Logger.h"

const Uint32 DOUBLE_CLICK_DELAY = 250;
const int DOUBLE_CLICK_RADIUS = 4;

void InputManager::update(SDL_Event& event) {
    // Reset wheel
    wheelUp = false;
    wheelDown = false;

    // Mouse
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            isLeftClick = true;
            Uint32 now = SDL_GetTicks();
            int x = event.button.x;
            int y = event.button.y;

            if ((now - lastClickTime < DOUBLE_CLICK_DELAY) &&
                abs(x - lastClickX) < DOUBLE_CLICK_RADIUS &&
                abs(y - lastClickY) < DOUBLE_CLICK_RADIUS) {
                isDoubleClick = true;
            }

            lastClickTime = now;
            lastClickX = x;
            lastClickY = y;
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

bool InputManager::isDoubleClicked() const { return isDoubleClick; }
void InputManager::deactivateDoubleClick() { isDoubleClick = false;}