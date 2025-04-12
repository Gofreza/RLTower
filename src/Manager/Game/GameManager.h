#pragma once

#include "MapManager.h"
#include "../Controls/InputManager.h"
#include "../UI/UiManager.h"
#include "../Characters/EnemyManager.h"
#include "../Config/Config.h"
#include "../Characters/CharactersManager.h"
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

    void toggleCombatMode();
    void stopCombatMode();

    void addCharacterToDefferedDeletions(Character* character);
    void deleteDeferredCharacters();
private:
    Player* player;
    std::vector<NPC*> npcs;
    std::vector<Enemy*> enemies;

    std::vector<Character*> characters;
    std::vector<Character*> deferredDeletions;

    std::vector<Cell*> cellsAffectedByEffects;

    int turn;
    size_t numberOfCharactersThatPlayedThisTurn;
    size_t currentCharacterIndex;

    bool combatMode;
    bool spellMode;
    bool cacMode;

    void playTurn();

    GameManager();
    ~GameManager();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
};