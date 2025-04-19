#pragma once

#include <SDL2/SDL.h>

class Config {
public:
    static Config& instance() {
        static Config instance;
        return instance;
    }

    // Getters
    bool isDebugMode() const;
    bool isShowFps() const;
    bool isArenaMode() const;
    SDL_Keycode getUpKey() const;
    SDL_Keycode getDownKey() const;
    SDL_Keycode getLeftKey() const;
    SDL_Keycode getRightKey() const;
    // Setters
    void setDebugMode(bool mode);
    void setShowFps(bool mode);
    void setArenaMode(bool mode);
    void setUpKey(SDL_Keycode key);
    void setDownKey(SDL_Keycode key);
    void setLeftKey(SDL_Keycode key);
    void setRightKey(SDL_Keycode key);

private:
    Config();
    ~Config();

    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete; 

    bool debugMode = false;
    bool showFps = false;
    bool isArena = false;

    SDL_Keycode upKey;
    SDL_Keycode downKey;
    SDL_Keycode leftKey;
    SDL_Keycode rightKey;
};
