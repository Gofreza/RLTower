#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Menu.h"
#include "../Misc/Utils.h"
#include "../Manager/Localization/LocalizationManager.h"
#include "../Manager/Characters/CharactersManager.h"
#include "../Manager/Controls/InputManager.h"
#include "../Character/Player.h"
#include "../Object/Item.h"
#include "../Object/Equipment/Weapon.h"
#include "../Object/Equipment/Shield.h"
#include "../Object/Equipment/Helmet.h"
#include "../Object/Equipment/Gloves.h"
#include "../Object/Equipment/Chests.h"
#include "../Object/Equipment/Leggings.h"
#include "../Object/Equipment/Ring.h"
#include "../Object/Equipment/Amulet.h"

class InventoryMenu : Menu
{
public:
    InventoryMenu(SDL_Renderer* renderer, TTF_Font* font);
    void render(const SDL_Rect& rect) override;

    int getHeight() const override;
    ~InventoryMenu();

    void toggleSpellsRendering();

private:
    int maxHeaderWidth;
    bool isRenderingSpells;
};
