#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <iostream>

#include "Menu.h"
#include "../Object/Item.h"
#include "../Manager/Localization/LocalizationManager.h"
#include "../Manager/Item/ItemManager.h"
#include "../Object/Equipment/Weapon.h"
#include "../Object/Equipment/Shield.h"
#include "../Object/Equipment/Helmet.h"
#include "../Object/Equipment/Gloves.h"
#include "../Object/Equipment/Chests.h"
#include "../Object/Equipment/Leggings.h"
#include "../Object/Equipment/Ring.h"
#include "../Object/Equipment/Amulet.h"
#include "../Object/Misc/Consumable.h"
#include "../Object/Misc/Projectile.h"

class ItemMenu : Menu
{
public:
    ItemMenu(SDL_Renderer* renderer, TTF_Font* font);
    void render(const SDL_Rect& rect) override;
    void render(const SDL_Rect& rect, Item* item);

    int getHeight() const override;
    ~ItemMenu();

private:
    SDL_Rect imgRect;
    SDL_Rect dataRect;

    void renderWithColor(int& currentY, SDL_Color color, std::string label, std::string value);
    void renderWithoutColor(int& currentY, std::string label, std::string value);

    void renderWeapon(Item* item, int& currentY);
    void renderShield(Item* item, int& currentY);
    void renderHelmet(Item* item, int& currentY);
    void renderGloves(Item* item, int& currentY);
    void renderChest(Item* item, int& currentY);
    void renderLegging(Item* item, int& currentY);
    void renderRing(Item* item, int& currentY);
    void renderAmulet(Item* item, int& currentY);
    void renderConsumable(Item* item, int& currentY);
    void renderProjectile(Item* item, int& currentY);
    void renderContainer(Item* item, int& currenY);
};