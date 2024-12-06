#pragma once

#include "MapManager.h"
#include "../Controls/InputManager.h"
#include "../UI/UiManager.h"
#include "../Characters/EnemyManager.h"
#include <SDL2/SDL.h>

using CharactersQueue = std::priority_queue<
    Character*, 
    std::vector<Character*>, 
    std::function<bool(Character*, Character*)>
>;

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

    bool movePlayer();
    void moveCharacter(Character* character, int dx, int dy);
private:
    Player* player;
    std::vector<NPC*> npcs;
    std::vector<Enemy*> enemies;

    CharactersQueue charactersQueue;
    std::vector<Character*> characters;

    int turn;
    size_t currentCharacterIndex;

    void playTurn();

    GameManager();
    ~GameManager();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
};