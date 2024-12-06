#include "Player.h"
#include "../Manager/Controls/InputManager.h"
#include "../Manager/Game/MapManager.h"
#include "../Manager/UI/UiManager.h"

Player::Player(const std::string& name, SDL_Color color, GroupType group, float hp, int mana, int energy, int stamina, int fov, int speed,
            int phyDamage, int magDamage, int strength, int dexterity,
            int intelligence, int wisdom, int constitution, int luck,
            const char symbol,
            std::vector<int> desires, std::vector<int> disgusts)
 : Character(name, color, group, hp, mana, energy, stamina, fov, speed, phyDamage, magDamage, strength, dexterity, intelligence, wisdom, constitution, luck, symbol, desires, disgusts)
{
}

Player::~Player()
{
}

bool Player::update()
{
    bool moved = false;
    if (InputManager::instance().isKeyPressed(SDLK_UP)) {
        InputManager::instance().deactivateKey(SDLK_UP);

        if (MapManager::instance().canPlayerMove(this, 0, -1)) {
            this->move(0, -1);
            MapManager::instance().movePlayerInMap(this, 0, -1);  
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(SDLK_DOWN)) {
        InputManager::instance().deactivateKey(SDLK_DOWN);

        if (MapManager::instance().canPlayerMove(this, 0, 1)) {
            this->move(0, 1);
            MapManager::instance().movePlayerInMap(this, 0, 1);
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(SDLK_LEFT)) {
        InputManager::instance().deactivateKey(SDLK_LEFT);

        if (MapManager::instance().canPlayerMove(this, -1, 0)) {
            this->move(-1, 0);
            MapManager::instance().movePlayerInMap(this, -1, 0);
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(SDLK_RIGHT)) {
        InputManager::instance().deactivateKey(SDLK_RIGHT);

        if (MapManager::instance().canPlayerMove(this, 1, 0)) {
            this->move(1, 0);
            MapManager::instance().movePlayerInMap(this, 1, 0);
            moved = true;
        }
    }
    if (moved) {
        UiManager::instance().updateGame(true);
    }
    return moved;
}