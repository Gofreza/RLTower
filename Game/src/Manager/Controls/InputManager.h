#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>

class InputManager {
public:
    static InputManager& instance() {
        static InputManager instance;
        return instance;
    }

    void update(SDL_Event& event);

    bool isKeyPressed(SDL_Keycode key);
    void deactivateKey(SDL_Keycode key);

    bool isLeftClicked();
    bool isRightClicked();
    void deactivateLeftClick();
    void deactivateRightClick();

    bool isWheelUp() const;
    bool isWheelDown() const;
    void deactivateWheelUp();
    void deactivateWheelDown();

private:
    std::unordered_map<SDL_Keycode, bool> keys;
    bool isLeftClick;
    bool isRightClick;

    bool wheelUp = false;
    bool wheelDown = false;
};
