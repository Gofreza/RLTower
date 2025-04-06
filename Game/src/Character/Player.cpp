#include "Player.h"
#include "../Manager/Controls/InputManager.h"
#include "../Manager/Game/MapManager.h"
#include "../Manager/UI/UiManager.h"

Player::Player(const std::string& name, SDL_Color color, GroupType group, const std::string& imagePath, const std::string& description,
            float hp, int mana, int energy, int stamina, bool isAuraUser, int fov, int speed,
            int phyDamage, int magDamage, int strength, int dexterity,
            int intelligence, int wisdom, int constitution, int luck,
            const char symbol,
            std::vector<int> desires, std::vector<int> disgusts)
 : Character(name, color, group, imagePath, description, hp, mana, energy, stamina, isAuraUser, fov, speed, phyDamage, magDamage, strength, dexterity, intelligence, wisdom, constitution, luck, symbol, desires, disgusts)
{
}

Player::~Player()
{
}

bool Player::update()
{   
    this->hasWaited = false;
    bool moved = false;
    bool attacked = false;
    if (InputManager::instance().isKeyPressed(SDLK_UP)) {
        InputManager::instance().deactivateKey(SDLK_UP);

        if (MapManager::instance().canPlayerMove(this, 0, -1)) {
            this->move(0, -1);
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(SDLK_DOWN)) {
        InputManager::instance().deactivateKey(SDLK_DOWN);

        if (MapManager::instance().canPlayerMove(this, 0, 1)) {
            this->move(0, 1);
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(SDLK_LEFT)) {
        InputManager::instance().deactivateKey(SDLK_LEFT);

        if (MapManager::instance().canPlayerMove(this, -1, 0)) {
            this->move(-1, 0);
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(SDLK_RIGHT)) {
        InputManager::instance().deactivateKey(SDLK_RIGHT);

        if (MapManager::instance().canPlayerMove(this, 1, 0)) {
            this->move(1, 0);
            moved = true;
        }
    }

    if (InputManager::instance().isKeyPressed(SDLK_SPACE)) {
        InputManager::instance().deactivateKey(SDLK_SPACE);
        // Toggle combat mode
        GameManager::instance().toggleCombatMode();
    }

    if (UiManager::instance().isMouseHoveringGame() && InputManager::instance().isWheelUp()) {
        InputManager::instance().deactivateWheelUp();
        this->hasWaited = true;
    }

    if (hasAttack) {
        attacked = true;
    }

    if (moved || hasWaited) {
        if (!overweight && this->stamina < this->maxStamina) {
            this->stamina += 1;
        } else if (overweight && this->stamina > 0) {
            this->stamina -= 1;
        }
        UiManager::instance().updateMenu(false);
    }

    Character::updateProgress();
    if (moved || attacked || hasWaited) {
        Character::update();
    }

    if (moved || attacked) {
        UiManager::instance().updateGame(true);
    }

    return moved || attacked || hasWaited;
}

void Player::move(int x, int y) {
    if (speed > 0) {
        Character::move(x, y);
        MapManager::instance().movePlayerInMap(this, x, y);
    }   
}

void Player::defend(Character* attacker)
{
    Character::defend(attacker);
    UiManager::instance().updateMenu(false);
}