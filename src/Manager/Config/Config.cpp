#include "Config.h"

Config::Config() {
    debugMode = false;
    showFps = false;

    upKey = SDLK_UP;
    downKey = SDLK_DOWN;
    leftKey = SDLK_LEFT;
    rightKey = SDLK_RIGHT;
}

Config::~Config() {}

bool Config::isDebugMode() const { return debugMode; }
bool Config::isShowFps() const { return showFps; }
bool Config::isArenaMode() const { return isArena; }
SDL_Keycode Config::getUpKey() const { return upKey; }
SDL_Keycode Config::getDownKey() const { return downKey; }
SDL_Keycode Config::getLeftKey() const { return leftKey; }
SDL_Keycode Config::getRightKey() const { return rightKey; }
// Setters
void Config::setDebugMode(bool mode) { debugMode = mode; } // Enable or disable debug mode
void Config::setShowFps(bool mode) { showFps = mode; } // Show or hide FPS counter
void Config::setArenaMode(bool mode) { isArena = mode; } // Mob don't attack the player
void Config::setUpKey(SDL_Keycode key) { upKey = key; }
void Config::setDownKey(SDL_Keycode key) { downKey = key; }
void Config::setLeftKey(SDL_Keycode key) { leftKey = key; }
void Config::setRightKey(SDL_Keycode key) { rightKey = key; }