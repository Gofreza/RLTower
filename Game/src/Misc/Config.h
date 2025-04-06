#pragma once

#include <SDL2/SDL.h>

class Config
{
public:
    Config();
    ~Config();

    // Getters
    bool isDebugMode() const;
    bool isShowFps() const;
    SDL_Keycode getUpKey() const;
    SDL_Keycode getDownKey() const;
    SDL_Keycode getLeftKey() const;
    SDL_Keycode getRightKey() const;
    // Setters
    void setDebugMode(bool mode);
    void setShowFps(bool mode);
    void setUpKey(SDL_Keycode key);
    void setDownKey(SDL_Keycode key);
    void setLeftKey(SDL_Keycode key);
    void setRightKey(SDL_Keycode key);

private:
    bool debugMode;
    bool showFps;

    SDL_Keycode upKey;
    SDL_Keycode downKey;
    SDL_Keycode leftKey;
    SDL_Keycode rightKey;
};
