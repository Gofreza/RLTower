#pragma once

#include "MapManager.h"
#include "../Controls/InputManager.h"
#include "../UI/UiManager.h"
#include "../Characters/EnemyManager.h"
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

    void movePlayer();
private:
    Player* player;
    std::vector<Enemy*> enemies;

    GameManager();
    ~GameManager();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
};