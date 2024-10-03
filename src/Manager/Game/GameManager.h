#pragma once

#include "MapManager.h"
#include <SDL2/SDL.h>

class GameManager
{
public:
    static GameManager& instance() {
        static GameManager instance;
        return instance;
    }

    void initialize();
    void update();
    void renderMap(SDL_Renderer* renderer, const SDL_Rect& rect, SDL_Texture* tileset, const std::vector<SDL_Rect>& tiles);
private:
    GameManager();
    ~GameManager();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
};